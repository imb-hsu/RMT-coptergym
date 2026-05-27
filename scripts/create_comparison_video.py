"""
==============================================================================
DRONE FLIGHT LOG VISUALIZER (SHOWCASE SCRIPT)
==============================================================================
Description:
This script reads drone telemetry data from CSV files and visualizes the flight
in a 3D environment using PyVista (VTK). 

Features:
- Dual-drone support (Agent vs Reference/INDI)
- High-resolution rendering with Anti-Aliasing (FHD, 4K)
- Telemetry Overlay: Beautiful transparent 2D Drone Schematic (Motor Health)
- Automatic model scaling & FRD to VTK transforms

==============================================================================
"""

import os
import ast
import numpy as np
import pandas as pd
import pyvista as pv
import matplotlib.pyplot as plt
import vtk

# Disable annoying VTK warnings in terminal
vtk.vtkObject.GlobalWarningDisplayOff()

# ============================================================
# --- WINDOWS HIGH-DPI FIX (Gegen das "Viertel-Bildschirm" Chart Problem) ---
if os.name == 'nt':
    import ctypes
    try:
        # Versucht den modernen DPI-Awareness Mode (Windows 10/11)
        ctypes.windll.shcore.SetProcessDpiAwareness(1)
    except Exception:
        # Fallback für ältere Windows-Versionen
        ctypes.windll.user32.SetProcessDPIAware()
# ============================================================

vtk.vtkObject.GlobalWarningDisplayOff()

# ============================================================
# ---------------------- USER SETTINGS -----------------------
# ============================================================

RES_720P  = (1280, 720)
RES_1080P = (1920, 1088)
RES_4K    = (3840, 2160)

RESOLUTION = RES_1080P       
VIDEO_FPS = 60               
SPEED_FACTOR = 1.0           
MAX_DURATION = 8            

SHOW_MOTOR_OVERLAY = True
FAIL_THRESHOLD = 0.45         # RPS limit: Motors below this value turn RED!
WARN_THRESHOLD = 0.175
SHOW_TRAJECTORY = True
VALIDATION_2D_PLOT = False   

GROUND_SIZE = 20
MODEL_SIZE = 0.275            


# ============================================================
# ------------------ FRD → VTK TRANSFORM ---------------------
# ============================================================

def frd_to_vtk_position(x, y, z):
    return y, x, -z

def frd_to_vtk_orientation(roll, pitch, yaw):
    return roll, -pitch, -yaw


# ============================================================
# --------------------- LOAD CSV DATA ------------------------
# ============================================================

def parse_vector_col(series):
    parsed_list =[]
    detected_len = 3
    for x in series:
        val = None
        if isinstance(x, (list, np.ndarray)): val = list(x)
        elif isinstance(x, str):
            x = x.strip()
            try: val = ast.literal_eval(x)
            except:
                try:
                    clean = x.replace('[','').replace(']','').replace('\n',' ')
                    parts = clean.split()
                    if parts: val =[float(v) for v in parts]
                except: val = None
        if val and hasattr(val, '__len__'): detected_len = len(val)
        parsed_list.append(val)
    
    final =[]
    zeros =[0.0]*detected_len
    for item in parsed_list:
        if item is None or len(item) != detected_len: final.append(zeros)
        else: final.append(item)
    return np.array(final)


def load_mission_csv(path):
    df = pd.read_csv(path)
    time = df["sim_time"] if "sim_time" in df else df["time"]
    pos  = parse_vector_col(df["agent_pos"])
    rpy  = parse_vector_col(df["agent_rpy_deg"])
    cmd  = parse_vector_col(df["action_cmd"]) 
    anom = parse_vector_col(df["anomaly_motorloss"]) 
    goal = parse_vector_col(df["mission_goal_pos"])
    return time, pos, rpy, cmd, anom, goal


def add_ground(plotter):
    # Ein leicht transparentes Gitter auf dem Boden
    grid = pv.Plane(center=(0, 0, 0), direction=(0, 0, 1), 
                    i_size=GROUND_SIZE, j_size=GROUND_SIZE, 
                    i_resolution=20, j_resolution=20)
    
    plotter.add_mesh(grid, style="wireframe", color="black", opacity=0.1, line_width=2)

    #plane = pv.Plane(
    #    center=(0, 0, 0), direction=(0, 0, 1),
    #    i_size=GROUND_SIZE, j_size=GROUND_SIZE
    #)
    #plotter.add_mesh(plane, color="lightgray", opacity=0.2)


# ============================================================
# --------------- GRAPHICAL TELEMETRY SCHEMATIC --------------
# ============================================================

def create_drone_schematic(num_motors, loc=(0.02, 0.72)):
    """
    Creates a clean, transparent 2D drawing of an X8 drone frame.
    No axes, no background - just the outlines and motor status points!
    """
    # WICHTIG: Das Verhältnis von Width zu Height MUSS für ein 16:9 Video
    # exakt 9/16 betragen, damit Kreise im HUD auch rund bleiben! 
    # Bei Height=0.25 ist Width=0.14
    chart = pv.Chart2D(size=(0.14, 0.25), loc=loc)
    
    # Alles unsichtbar machen (Hintergrund, Rahmen, Achsen)
    chart.background_color = (1.0, 1.0, 1.0, 0.0) 
    chart.border_color = 'black'
    
    chart.x_label=""
    chart.y_label=""
    chart.x_axis.tick_labels_visible = False
    chart.y_axis.tick_labels_visible = False
    chart.x_axis.tick_size = 0
    chart.y_axis.tick_size = 0
    chart.x_axis.pen.color = (0, 0, 0, 0)
    chart.y_axis.pen.color = (0, 0, 0, 0)
    chart.x_axis.grid = False
    chart.y_axis.grid = False
    
    # Etwas mehr Puffer, damit dicke Ränder nicht abgeschnitten werden
    chart.x_axis.range = [-1.4, 1.4]
    chart.y_axis.range =[-1.4, 1.4]
    
    # 3. Zentrum (Schwarze Outline)
    chart.scatter([0],[0], color="black", size=78, style="s")
    # 2. X-Frame Arme zeichnen (Eine dicke massive Linie statt 2 kleine!)
    # Arm 1: Hinten-Links nach Vorne-Rechts
    chart.line([-1, 1], [-1, 1], color="black", width=16)
    chart.line([-1, 1], [-1, 1], color="white", width=8)
    # Arm 2: Vorne-Links nach Hinten-Rechts
    chart.line([-1, 1], [1, -1], color="black", width=15)
    chart.line([-1, 1], [1, -1], color="white", width=8)
    # 3. Zentrum (weiß gefüllt)
    chart.scatter([0],[0], color="white", size=70, style="s")
    
    # 4. Nase / Forward-Indikator (kleines Dreieck vorne)
    #chart.area([-0.001,-0.2, 0, 0.2, -0.2, 0.001],[0,-0.2, 0.25, -0.2, -0.2,0], color="black")# liner with add  -0.2, -0.2, width=3)
    # X-Koordinaten: Links, Mitte, Rechts
    x = [-0.3, 0.0, 0.3]
    # Y1 (Unterkante): Bleibt flach bei 0.8
    y_bottom =[-0.3, -0.3, -0.3]
    # Y2 (Oberkante): Geht in der Mitte hoch auf 1.3
    y_top =[-0.25, 0.25, -0.25]
    
    chart.area(x, y_bottom, y_top, color="black")
    
    # 5. Motoren-Mapping (X8 Layout)
    positions =[
        ( 1.1,  1.1),  # M1 (Front-Right, Outer)
        (-1.1, -1.1),  # M2 (Rear-Left, Outer)
        (-1.1,  1.1),  # M3 (Front-Left, Outer)
        ( 1.1, -1.1),  # M4 (Rear-Right, Outer)
        ( 0.75, 0.75), # M5 (Front-Right, Inner)
        (-0.75,-0.75), # M6 (Rear-Left, Inner)
        (-0.75, 0.75), # M7 (Front-Left, Inner)
        ( 0.75,-0.75)  # M8 (Rear-Right, Inner)
    ]
    
    motor_plots =[]
    for i in range(min(num_motors, 8)):
        x, y = positions[i]
        size = 30 if i < 4 else 25
        
        # Zuerst ein größerer schwarzer Kreis als Outline
        chart.scatter([x], [y], color="black", size=size+8, style="o")
        # Dann der farbige (grün/rot) Kreis darüber
        m_plot = chart.scatter([x], [y], color="green", size=size, style="o")
        motor_plots.append(m_plot)
        
    return chart, motor_plots


def update_motor_schematic(motor_plots, motor_values):
    for i in range(len(motor_plots)):
        if motor_values[i] > FAIL_THRESHOLD:
            motor_plots[i].color = "red" 
        elif motor_values[i] > WARN_THRESHOLD:
            motor_plots[i].color = "orange" 
        else:
            motor_plots[i].color ="green"


# ============================================================
# ----------------------- MAIN LOOP --------------------------
# ============================================================

def main(path1, path2, model_path, output_video, agent1_name, agent2_name):
    print(f"Loading Primary Data: {path1}")

    # 1. Load Data
    t1, pos1, rpy1, cmd1, anomaly, goal1 = load_mission_csv(path1)
    if path2 is not None:
        t2, pos2, rpy2, cmd2, motors2, goal2 = load_mission_csv(path2)
    else:
        pos2 = rpy2 = motors2 = None

    duration = min((t1.iloc[-1] - t1[0]) / SPEED_FACTOR, MAX_DURATION)
    print(f"Rendering Duration: {duration:.2f}s at {VIDEO_FPS} FPS")
    
    n_frames = int(duration * VIDEO_FPS)
    idx = np.linspace(0, len(t1) - 1, n_frames).astype(int)

    # 2. Setup Plotter 
    plotter = pv.Plotter(window_size=RESOLUTION, off_screen=True)
    plotter.set_background(color="white")#, top="lightblue")     
    plotter.enable_lightkit() 
    plotter.enable_anti_aliasing('fxaa') 

    plotter.enable_ssao(radius=0.5, bias=0.01) 

    # 1. Standardlichter löschen
    #plotter.remove_all_lights()
    # 2. Hauptlicht (Sonne) - schräg von oben rechts
    #light1 = pv.Light(position=(20, 20, 20), focal_point=(0, 0, 0), 
    #                  color="#FFFFFF", intensity=0.8, light_type='scene light')
    #plotter.add_light(light1)
    # 3. Füll-Licht (sanftes Gegenlicht) - schräg von unten links
    light2 = pv.Light(position=(-10, -10, 50), focal_point=(0, 0, 35), 
                      color="#F3E34F", intensity=0.5, light_type='scene light')
    plotter.add_light(light2)

    #add_ground(plotter)

    # 3. Load & Process Drone Model
    drone_mesh = pv.read(model_path)
    drone_mesh.points -= drone_mesh.center
    
    x_len = drone_mesh.bounds[1] - drone_mesh.bounds[0]
    y_len = drone_mesh.bounds[3] - drone_mesh.bounds[2]
    max_len = max(x_len, y_len)
    drone_mesh.points *= (MODEL_SIZE / max_len) 

    drone1 = plotter.add_mesh(drone_mesh.copy(), 
                              opacity=0.85, 
                              color="#199bf8",       # Ein schönes Blau
                              pbr=True,              # Physikalisches Rendering an!
                              metallic=0.25,          # Leicht metallisch
                              roughness=0.5,         # Reflektiert Licht
                              smooth_shading=True,
                              show_edges=True,       # Runde Kanten
                              edge_color='black')   # Runde Kanten
     
    if pos2 is not None:
        drone2 = plotter.add_mesh(drone_mesh.copy(), 
                                  opacity=0.85,
                                  color="#d80a0a",   # Ein schönes Rot
                                  pbr=True, 
                                  metallic=0.25, 
                                  roughness=0.5, 
                                  smooth_shading=True,
                                  show_edges=True,       # Runde Kanten
                                  edge_color='black')   # Runde Kanten

    # 4. Trajectories & Target
    sphere = pv.Sphere(radius=0.04, center=(0,0,0), theta_resolution=60, phi_resolution=60)
    target1 = plotter.add_mesh(sphere, color="yellow",edge_color="black", ambient=0.5, pbr=True)

    traj1, traj2 = [],[]

    # 5. Initialize ONLY ONE Graphical HUD (for Primary Agent)
    if SHOW_MOTOR_OVERLAY and anomaly is not None:
        num_m1 = len(anomaly[0])
        # Das HUD wird erstellt (Y-Start=0.68, Y-Ende ist 0.68+0.25=0.93 -> sicher im Bild!)
        chart1, chart_circles1 = create_drone_schematic(num_m1) #.68))
        plotter.add_chart(chart1)

    # 6. Add Clean Text Legend next to the HUD
    # Text sitzt jetzt neben dem HUD (X=0.18) und auf exakt passender Höhe
    title_text = plotter.add_text("UAV Simulation: Intermittend Actuator Dropout", position=(0.18, 0.91), color="black", font_size=26, viewport=True)
    title_text.GetTextProperty().SetBold(True)
    #plotter.add_text("Flugverhaltens unter Motorausfall", position=(0.18, 0.91), color="black", font_size=26, viewport=True)
    plotter.add_text(f"{agent1_name}", position=(0.18, 0.845), color="#2287cf", font_size=26, viewport=True)
    if pos2 is not None:
        plotter.add_text(f"{agent2_name}", position=(0.18, 0.78), color="#c11212", font_size=26, viewport=True)

    
    # 1. Wir erstellen eine leere 2D-Chart als Hintergrund-Panel
    alarm_box = pv.Chart2D(size=(0.33, 0.05), loc=(0.18, 0.72))
    
    # Achsen und Raster komplett ausblenden
    alarm_box.x_axis.tick_labels_visible = False
    alarm_box.y_axis.tick_labels_visible = False
    alarm_box.x_axis.tick_size = 0
    alarm_box.y_axis.tick_size = 0
    alarm_box.x_axis.pen.color = (0, 0, 0, 0)
    alarm_box.y_axis.pen.color = (0, 0, 0, 0)
    alarm_box.x_axis.grid = False
    alarm_box.y_axis.grid = False
    
    # Startfarbe (Grün) und Rahmen setzen
    alarm_box.background_color = (0.0, 0.6, 0.0, 1.0) 
    alarm_box.border_color = (0.0, 0.0, 0.0, 1.0)
    alarm_box.border_width = 2
    
    plotter.add_chart(alarm_box)

    # 2. Wir legen den Text als reines Overlay EXAKT in die Mitte dieser Box
    # Die Box geht von X=0.18 bis 0.46 und Y=0.71 bis 0.76.
    # Text bei X=0.19, Y=0.725 zentriert ihn optisch perfekt!
    warning_text = plotter.add_text("---", position=(0.21, 0.7175), color="white", font_size=26, viewport=True)
    #warning_text.GetTextProperty().SetBold(True) 


    # 7. Fixed Camera Setup & The "Invisible Start" Bugfix
    cameraset_topdown = [
        (0.2, -0.3, 19),   
        (0.2, 0.5, 11),    
        (1.0, 0, 0)        
    ]
    cameraset_diagonal =[
        (2, -2.5, 19), # x, y, z Position der Kamera (VTK Koordinaten!)
        (0, -0.3, 15),      # Focal Point (wohin die Kamera schaut, hier die Mitte des Bodens)
        (-0.9, -0.25, 0.34)       # Up-Vektor (Z ist oben)
        ]

    plotter.camera_position =cameraset_topdown #cameraset_diagonal
   

    plotter.camera.clipping_range = (0.01, 10000)
    plotter.show(auto_close=False, interactive_update=True)

    # 8. Render Video
    plotter.open_movie(output_video, framerate=VIDEO_FPS)

    for i in idx:
        gx, gy, gz = frd_to_vtk_position(*goal1[i])
        target1.SetPosition([gx, gy, gz])
    
        x, y, z = frd_to_vtk_position(*pos1[i])
        drone1.SetPosition([x, y, z])
        r, p, yw = frd_to_vtk_orientation(*rpy1[i])
        drone1.SetOrientation([r, p, yw])

        if SHOW_TRAJECTORY:
            traj1.append([x, y, z])
            if len(traj1) > 1:
                line = pv.lines_from_points(np.array(traj1))
                plotter.add_mesh(line, color="#0869af", name="traj_line_1", reset_camera=False, render_lines_as_tubes=True, line_width=4, lighting=False)

        if pos2 is not None:
            x2, y2, z2 = frd_to_vtk_position(*pos2[i])
            drone2.SetPosition([x2, y2, z2])
            r2, p2, yw2 = frd_to_vtk_orientation(*rpy2[i])
            drone2.SetOrientation([r2, p2, yw2])

            if SHOW_TRAJECTORY:
                traj2.append([x2, y2, z2])
                if len(traj2) > 1:
                    line2 = pv.lines_from_points(np.array(traj2))
                    plotter.add_mesh(line2, color="#af0808", name="traj_line_2", reset_camera=False, render_lines_as_tubes=True, line_width=4, lighting=False)

        # Update HUD Health State & Schematic
        if SHOW_MOTOR_OVERLAY and anomaly is not None:
            update_motor_schematic(chart_circles1, anomaly[i])
            
            # --- NEU: MASTER ALARM LOGIK ---
            # Prüft, ob irgendein Motor unter den Fail-Threshold gefallen ist
            if np.any(np.array(anomaly[i]) > FAIL_THRESHOLD):
                # FEHLER-FALL: Text ändern und Kasten auf KNALLROT schalten
                warning_text.SetInput(" ANOMALY - DEFECT ")
                warning_text.SetPosition((0.208, 0.7175))
                alarm_box.background_color = (0.8, 0.0, 0.0, 1.0) 
            elif np.any(np.array(anomaly[i]) > WARN_THRESHOLD):
                # FEHLER-FALL: Text ändern und Kasten auf KNALLROT schalten
                warning_text.SetInput(" ANOMALY - WARNING ")
                warning_text.SetPosition((0.18, 0.7175))
                alarm_box.background_color = (0.4, 0.4, 0.0, 1.0) 
            else:
                # NORMAL-FALL: Text zurücksetzen und Kasten auf GRÜN schalten
                warning_text.SetInput(" SYSTEM NOMINAL  ")
                warning_text.SetPosition((0.22, 0.7175))
                alarm_box.background_color = (0.0, 0.6, 0.0, 1.0)

        plotter.update()       
        plotter.write_frame()  
    
    plotter.close()
    print(f"Video saved successfully: {output_video}")


if __name__ == "__main__":
    try:
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    except NameError:
        project_root = "."

    print("project_root: ",project_root)

    output_dir = os.path.join(project_root, "data", "visualization", "x8_copter_Compare_Blind_INDI_IAD.mp4")
    model_dir = os.path.join(project_root, "data", "visualization", "3dmodels", "KopixX8_Demo.obj")
    
    agent = os.path.join(project_root, "data", "Evaluation", "Raw_Files", "RL_Add_Blind", "Intermittent_Actuator_Dropout", "Benchmark_Spiral", "run_0.csv")
    ftc = os.path.join(project_root, "data", "Evaluation", "Raw_Files", "FTC_DMotor_Blind", "Intermittent_Actuator_Dropout", "Benchmark_Spiral", "run_0.csv")
    indi = os.path.join(project_root, "data", "INDI", "Intermittent_Actuator_Dropout", "Benchmark_Spiral", "benchmark_results.csv")
    
    print("data paths: /mnt/c/Users/MarkTappe/Desktop/GIT/GitHub3/RMT-coptergym/data/INDI/Intermittent_Actuator_Dropout/Benchmark_Spiral/benchmark_results.csv ")

    main(path1=indi, 
         path2=agent, 
         model_path=model_dir, 
         output_video=output_dir,
         agent1_name="INDI", 
         agent2_name="DRL (Add Blind)")

#    main(path1=indi, 
#         path2=None,
#         model_path=model_dir, 
#         output_video=output_dir,
#         agent1_name="classical INDI" ,
#         agent2_name=None)