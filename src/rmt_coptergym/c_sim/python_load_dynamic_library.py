import ctypes
import os
# Importieren aller ctypes-Strukturen aus der Begleitdatei
from rmt_coptergym.c_sim.RMT_structs import ExtU_RMT_FDM_DLL_FrameWork_FCS_RT_T, ExtY_RMT_FDM_DLL_FrameWork_FCS_RT_T

class Simulator:
    """
    Eine Wrapper-Klasse zur Interaktion mit der RMT_FDM_DLL_FrameWork_FCS_RT
    Shared Library.
    """
    def __init__(self, lib_path: str):
        """
        Lädt die Bibliothek, findet die globalen Ein-/Ausgabestrukturen und
        initialisiert das FDM-Modell.

        :param lib_path: Der Pfad zur .so (Linux/macOS) oder .dll (Windows) Datei.
        """
        if not os.path.exists(lib_path):
            raise FileNotFoundError(f"Bibliothek nicht gefunden unter: {lib_path}")

        # 1. Bibliothek laden (entspricht dlopen)
        self.lib = ctypes.CDLL(lib_path)
        print(f"Bibliothek '{lib_path}' erfolgreich geladen.")

        # 2. Funktionsprototypen definieren (entspricht dlsym für Funktionen)
        # Dies ist gute Praxis für Typsicherheit und Fehlerprüfung.
        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_initialize.argtypes = []
        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_initialize.restype = None
        
        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_step.argtypes = []
        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_step.restype = None

        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_terminate.argtypes = []
        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_terminate.restype = None

        # 3. Globale Ein- und Ausgabestrukturen holen (entspricht dlsym für Variablen)
        try:
            # Der Name der globalen Variable in der DLL
            u_symbol = "RMT_FDM_DLL_FrameWork_FCS_RT_U"
            y_symbol = "RMT_FDM_DLL_FrameWork_FCS_RT_Y"
            
            self.inputs = ExtU_RMT_FDM_DLL_FrameWork_FCS_RT_T.in_dll(self.lib, u_symbol)
            self.outputs = ExtY_RMT_FDM_DLL_FrameWork_FCS_RT_T.in_dll(self.lib, y_symbol)
            print(f"Globale Strukturen '{u_symbol}' und '{y_symbol}' erfolgreich gefunden.")
        except ValueError:
            print(f"Fehler: Konnte die globalen Strukturen '{u_symbol}' oder '{y_symbol}' nicht finden.")
            print("Stellen Sie sicher, dass die Bibliothek mit exportierten globalen Variablen kompiliert wurde.")
            raise

        # 4. Modell initialisieren
        print("Initialisiere das FDM-Modell...")
        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_initialize()
        print("Initialisierung abgeschlossen.")

    def step(self):
        """Führt einen einzelnen Simulationsschritt aus."""
        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_step()

    def terminate(self):
        """Ruft die Terminate-Funktion der Bibliothek auf."""
        print("Terminiere die Simulation...")
        self.lib.RMT_FDM_DLL_FrameWork_FCS_RT_terminate()
        print("Bibliothek erfolgreich terminiert.")


# Hauptlogik, die den C-Code nachbildet
if __name__ == "__main__":
    # Pfad zur Shared Library (.so für Linux, .dll für Windows)
    # Stellen Sie sicher, dass die Bibliothek im selben Verzeichnis liegt oder geben Sie den vollen Pfad an.
    library_path = "./RMT_FDM_DLL_FrameWork_FCS_RT.dll"

    # Simulator-Instanz erstellen
    sim = Simulator(library_path)
    sim2 = Simulator(library_path)

    try:
        # Die äußere Schleife aus dem C-Code
        for run_idx in range(4):
            print(f"\n--- Starte Durchlauf {run_idx + 1}/4 ---")

            # --- Setzen der Initialbedingungen (genau wie im C-Code) ---
            sim.inputs.States_Init.vel_K_R_E_B_mDs.u_K_R_E_B_mDs = 0.0
            sim.inputs.States_Init.vel_K_R_E_B_mDs.v_K_R_E_B_mDs = 0.0
            sim.inputs.States_Init.vel_K_R_E_B_mDs.w_K_R_E_B_mDs = 0.0

            sim.inputs.States_Init.rot_K_IB_B_radDs.w_x_K_IB_B_radDs = 0.0
            sim.inputs.States_Init.rot_K_IB_B_radDs.w_y_K_IB_B_radDs = 0.0
            sim.inputs.States_Init.rot_K_IB_B_radDs.w_z_K_IB_B_radDs = 0.0

            sim.inputs.States_Init.att_euler_rad.Phi_rad = 0.0
            sim.inputs.States_Init.att_euler_rad.Theta_rad = 0.0
            sim.inputs.States_Init.att_euler_rad.Psi_rad = 0.0

            sim.inputs.States_Init.pos_R_O_m.x_R_O_m = 0.0
            sim.inputs.States_Init.pos_R_O_m.y_R_O_m = 0.0
            sim.inputs.States_Init.pos_R_O_m.z_R_O_m = -10.0

            sim.inputs.States_Init.pos_R_WGS84.lambda_R_WGS84_rad = 0.2033
            sim.inputs.States_Init.pos_R_WGS84.mue_R_WGS84_rad = 0.8439
            sim.inputs.States_Init.pos_R_WGS84.h_R_WGS84_m = 548.0

            # Setzen der initialen Aktuator-Zustände
            for i in range(8):
                sim.inputs.States_Init.actuator.u_0_radDs[i] = 823.0

            # --- Spezielle Initialisierungssequenz mit zwei step()-Aufrufen ---
            
            # Erster step() zur Vorbereitung
            sim.inputs.Simulation_Control.flg_Reset = False
            sim.inputs.Simulation_Control.flg_Run = False
            sim.inputs.Simulation_Control.flg_Enable_Controller = False
            sim.inputs.fc_pilot_cmd.arm_swi = False
            sim.inputs.fc_pilot_cmd.override_swi = True
            sim.inputs.fc_pilot_cmd.vel_att_mode_swi = True
            sim.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs = -2.0
            sim.step()

            # Zweiter step() zum Zurücksetzen und Anwenden der Initialwerte
            sim.inputs.Simulation_Control.flg_Reset = True
            sim.inputs.Simulation_Control.flg_Run = False
            sim.inputs.Simulation_Control.flg_Enable_Controller = True
            sim.inputs.fc_pilot_cmd.arm_swi = True
            sim.inputs.fc_pilot_cmd.override_swi = True
            sim.inputs.fc_pilot_cmd.vel_att_mode_swi = True
            sim.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs = -2.0
            sim.step()

            # Ausgabe nach der Initialisierung
            w_cmd = sim.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs
            z_dot = sim.outputs.Vehicle.Outputs.States_Dot.pos_dot_R_E_O_mDs.z_dot_R_E_O_mDs
            z_pos = sim.outputs.Vehicle.States.pos_R_O_m.z_R_O_m
            w1_meas = sim.outputs.Measurements.motor_meas.w1_meas_radDs
            print(f"Zustände initialisiert: w_cmd={w_cmd}, z_dot={z_dot:.4f}, z_pos={z_pos:.4f}, w1_meas={w1_meas:.4f}")
            print("Starte jetzt die Simulation...")

            # --- Haupt-Simulationslauf ---

            # ---------------- sim2! 
            # Simulations-Flags setzen
            sim2.inputs.Simulation_Control.flg_Reset = False
            sim2.inputs.Simulation_Control.flg_Run = True
            sim2.inputs.Simulation_Control.flg_Run_p = True
            sim2.inputs.Simulation_Control.flg_Run_q = True
            sim2.inputs.Simulation_Control.flg_Run_r = True
            sim2.inputs.Simulation_Control.flg_Run_Phi = True
            sim2.inputs.Simulation_Control.flg_Run_Theta = True
            sim2.inputs.Simulation_Control.flg_Run_Psi = True
            sim2.inputs.Simulation_Control.flg_Run_vel_x = True
            sim2.inputs.Simulation_Control.flg_Run_vel_y = True
            sim2.inputs.Simulation_Control.flg_Run_vel_z = True
            sim2.inputs.Simulation_Control.flg_Run_pos_x = True
            sim2.inputs.Simulation_Control.flg_Run_pos_y = True
            sim2.inputs.Simulation_Control.flg_Run_pos_z = True
            sim2.inputs.Simulation_Control.flg_Propulsion_On = True
            sim2.inputs.Simulation_Control.flg_Aerodynamics_On = True
            sim2.inputs.Simulation_Control.flg_Weight_Balance_On = True
            sim2.inputs.Simulation_Control.flg_Ground_Contacts_On = False
            sim2.inputs.Simulation_Control.flg_Enable_Sensor_Errors = False
            sim2.inputs.Simulation_Control.flg_Enable_Controller = False


            print(f"\n--- Starte Durchlauf {run_idx + 1}/4 ---")

            # --- Setzen der Initialbedingungen (genau wie im C-Code) ---
            sim2.inputs.States_Init.vel_K_R_E_B_mDs.u_K_R_E_B_mDs = 0.0
            sim2.inputs.States_Init.vel_K_R_E_B_mDs.v_K_R_E_B_mDs = 0.0
            sim2.inputs.States_Init.vel_K_R_E_B_mDs.w_K_R_E_B_mDs = 0.0

            sim2.inputs.States_Init.rot_K_IB_B_radDs.w_x_K_IB_B_radDs = 0.0
            sim2.inputs.States_Init.rot_K_IB_B_radDs.w_y_K_IB_B_radDs = 0.0
            sim2.inputs.States_Init.rot_K_IB_B_radDs.w_z_K_IB_B_radDs = 0.0

            sim2.inputs.States_Init.att_euler_rad.Phi_rad = 0.0
            sim2.inputs.States_Init.att_euler_rad.Theta_rad = 0.0
            sim2.inputs.States_Init.att_euler_rad.Psi_rad = 0.0

            sim2.inputs.States_Init.pos_R_O_m.x_R_O_m = 0.0
            sim2.inputs.States_Init.pos_R_O_m.y_R_O_m = 0.0
            sim2.inputs.States_Init.pos_R_O_m.z_R_O_m = -10.0

            sim2.inputs.States_Init.pos_R_WGS84.lambda_R_WGS84_rad = 0.2033
            sim2.inputs.States_Init.pos_R_WGS84.mue_R_WGS84_rad = 0.8439
            sim2.inputs.States_Init.pos_R_WGS84.h_R_WGS84_m = 548.0

            # Setzen der initialen Aktuator-Zustände
            for i in range(8):
                sim2.inputs.States_Init.actuator.u_0_radDs[i] = 823.0

            # --- Spezielle Initialisierungssequenz mit zwei step()-Aufrufen ---
            
            # Erster step() zur Vorbereitung
            sim2.inputs.Simulation_Control.flg_Reset = False
            sim2.inputs.Simulation_Control.flg_Run = False
            sim2.inputs.Simulation_Control.flg_Enable_Controller = False
            sim2.inputs.fc_pilot_cmd.arm_swi = False
            sim2.inputs.fc_pilot_cmd.override_swi = True
            sim2.inputs.fc_pilot_cmd.vel_att_mode_swi = True
            sim2.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs.u_K_R_E_C_cmd_mDs = -2.0
            sim2.step()

            # Zweiter step() zum Zurücksetzen und Anwenden der Initialwerte
            sim2.inputs.Simulation_Control.flg_Reset = True
            sim2.inputs.Simulation_Control.flg_Run = False
            sim2.inputs.Simulation_Control.flg_Enable_Controller = True
            sim2.inputs.fc_pilot_cmd.arm_swi = True
            sim2.inputs.fc_pilot_cmd.override_swi = True
            sim2.inputs.fc_pilot_cmd.vel_att_mode_swi = True
            sim2.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs.u_K_R_E_C_cmd_mDs = -2.0
            sim2.step()

            # Ausgabe nach der Initialisierung
            u_cmd = sim2.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs.u_K_R_E_C_cmd_mDs
            z_dot = sim2.outputs.Vehicle.Outputs.States_Dot.pos_dot_R_E_O_mDs.z_dot_R_E_O_mDs
            z_pos = sim2.outputs.Vehicle.States.pos_R_O_m.z_R_O_m
            w1_meas = sim2.outputs.Measurements.motor_meas.w1_meas_radDs
            print(f"Zustände initialisiert: u_cmd={u_cmd}, z_dot={z_dot:.4f}, z_pos={z_pos:.4f}, w1_meas={w1_meas:.4f}")
            print("Starte jetzt die Simulation...")

            # --- Haupt-Simulationslauf ---

            # Simulations-Flags setzen
            sim.inputs.Simulation_Control.flg_Reset = False
            sim.inputs.Simulation_Control.flg_Run = True
            sim.inputs.Simulation_Control.flg_Run_p = True
            sim.inputs.Simulation_Control.flg_Run_q = True
            sim.inputs.Simulation_Control.flg_Run_r = True
            sim.inputs.Simulation_Control.flg_Run_Phi = True
            sim.inputs.Simulation_Control.flg_Run_Theta = True
            sim.inputs.Simulation_Control.flg_Run_Psi = True
            sim.inputs.Simulation_Control.flg_Run_vel_x = True
            sim.inputs.Simulation_Control.flg_Run_vel_y = True
            sim.inputs.Simulation_Control.flg_Run_vel_z = True
            sim.inputs.Simulation_Control.flg_Run_pos_x = True
            sim.inputs.Simulation_Control.flg_Run_pos_y = True
            sim.inputs.Simulation_Control.flg_Run_pos_z = True
            sim.inputs.Simulation_Control.flg_Propulsion_On = True
            sim.inputs.Simulation_Control.flg_Aerodynamics_On = True
            sim.inputs.Simulation_Control.flg_Weight_Balance_On = True
            sim.inputs.Simulation_Control.flg_Ground_Contacts_On = False
            sim.inputs.Simulation_Control.flg_Enable_Sensor_Errors = False
            sim.inputs.Simulation_Control.flg_Enable_Controller = False

            sim2.inputs.Simulation_Control.flg_Reset = False
            sim2.inputs.Simulation_Control.flg_Run = True
            sim2.inputs.Simulation_Control.flg_Run_p = True
            sim2.inputs.Simulation_Control.flg_Run_q = True
            sim2.inputs.Simulation_Control.flg_Run_r = True
            sim2.inputs.Simulation_Control.flg_Run_Phi = True
            sim2.inputs.Simulation_Control.flg_Run_Theta = True
            sim2.inputs.Simulation_Control.flg_Run_Psi = True
            sim2.inputs.Simulation_Control.flg_Run_vel_x = True
            sim2.inputs.Simulation_Control.flg_Run_vel_y = True
            sim2.inputs.Simulation_Control.flg_Run_vel_z = True
            sim2.inputs.Simulation_Control.flg_Run_pos_x = True
            sim2.inputs.Simulation_Control.flg_Run_pos_y = True
            sim2.inputs.Simulation_Control.flg_Run_pos_z = True
            sim2.inputs.Simulation_Control.flg_Propulsion_On = True
            sim2.inputs.Simulation_Control.flg_Aerodynamics_On = True
            sim2.inputs.Simulation_Control.flg_Weight_Balance_On = True
            sim2.inputs.Simulation_Control.flg_Ground_Contacts_On = False
            sim2.inputs.Simulation_Control.flg_Enable_Sensor_Errors = False
            sim2.inputs.Simulation_Control.flg_Enable_Controller = False

            # Die innere Schleife
            for i in range(5):
                # Setzen der direkten Motorbefehle (falls Controller deaktiviert wäre)
                for cmd_idx in range(8):
                    sim.inputs.w_cmd_radDs[cmd_idx] = 832.0
                    sim2.inputs.w_cmd_radDs[cmd_idx] = 0.0
                
                # Setzen der Pilotenkommandos für jeden Schritt
                sim.inputs.fc_pilot_cmd.arm_swi = True
                sim.inputs.fc_pilot_cmd.override_swi = True
                sim.inputs.fc_pilot_cmd.vel_att_mode_swi = True
                sim.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs = -2.0

                # Setzen der Pilotenkommandos für jeden Schritt
                sim2.inputs.fc_pilot_cmd.arm_swi = True
                sim2.inputs.fc_pilot_cmd.override_swi = True
                sim2.inputs.fc_pilot_cmd.vel_att_mode_swi = True
                sim2.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs.u_K_R_E_C_cmd_mDs = -2.0
                
                # Simulationsschritt ausführen
                sim.step()
                sim2.step()

                print(f"{i}: --> {i * 0.004:.3f}(s)")
                # Motorwerte

                print("  Motorwerte:  "
                    f"{sim.outputs.Vehicle.Commands.w1_act_radDs:.3f} "
                    f"{sim.outputs.Vehicle.Commands.w2_act_radDs:.3f} "
                    f"{sim.outputs.Vehicle.Commands.w3_act_radDs:.3f} "
                    f"{sim.outputs.Vehicle.Commands.w4_act_radDs:.3f} "
                    f"{sim.outputs.Vehicle.Commands.w5_act_radDs:.3f} "
                    f"{sim.outputs.Vehicle.Commands.w6_act_radDs:.3f} "
                    f"{sim.outputs.Vehicle.Commands.w7_act_radDs:.3f} "
                    f"{sim.outputs.Vehicle.Commands.w8_act_radDs:.3f}"
                )

                # Position

                print("  Position:    "
                    f"{sim.outputs.Vehicle.States.pos_R_O_m.x_R_O_m:.3f} "
                    f"{sim.outputs.Vehicle.States.pos_R_O_m.y_R_O_m:.3f} "
                    f"{sim.outputs.Vehicle.States.pos_R_O_m.z_R_O_m:.3f}"
                )

                # Geschwindigkeiten
                print("  Velocities:  "
                    f"{sim.outputs.Vehicle.Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.u_K_R_E_B_mDs:.3f} "
                    f"{sim.outputs.Vehicle.Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.v_K_R_E_B_mDs:.3f} "
                    f"{sim.outputs.Vehicle.Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.w_K_R_E_B_mDs:.3f}"
                )

                print("2 Motorwerte:  "
                    f"{sim2.outputs.Vehicle.Commands.w1_act_radDs:.3f} "
                    f"{sim2.outputs.Vehicle.Commands.w2_act_radDs:.3f} "
                    f"{sim2.outputs.Vehicle.Commands.w3_act_radDs:.3f} "
                    f"{sim2.outputs.Vehicle.Commands.w4_act_radDs:.3f} "
                    f"{sim2.outputs.Vehicle.Commands.w5_act_radDs:.3f} "
                    f"{sim2.outputs.Vehicle.Commands.w6_act_radDs:.3f} "
                    f"{sim2.outputs.Vehicle.Commands.w7_act_radDs:.3f} "
                    f"{sim2.outputs.Vehicle.Commands.w8_act_radDs:.3f}"
                )

                # Position

                print("2 Position:    "
                    f"{sim2.outputs.Vehicle.States.pos_R_O_m.x_R_O_m:.3f} "
                    f"{sim2.outputs.Vehicle.States.pos_R_O_m.y_R_O_m:.3f} "
                    f"{sim2.outputs.Vehicle.States.pos_R_O_m.z_R_O_m:.3f}"
                )

                # Geschwindigkeiten
                print("2 Velocities:  "
                    f"{sim2.outputs.Vehicle.Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.u_K_R_E_B_mDs:.3f} "
                    f"{sim2.outputs.Vehicle.Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.v_K_R_E_B_mDs:.3f} "
                    f"{sim2.outputs.Vehicle.Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.w_K_R_E_B_mDs:.3f}"
                )

            
            # --- Zurücksetzen am Ende des Durchlaufs ---
            print("Setze Simulation für nächsten Durchlauf zurück...")
            sim.inputs.Simulation_Control.flg_Run = False
            sim.inputs.Simulation_Control.flg_Reset = False # Im C-Code steht hier false
            sim.step()

            sim2.inputs.Simulation_Control.flg_Run = False
            sim2.inputs.Simulation_Control.flg_Reset = False # Im C-Code steht hier false
            sim2.step()

    except Exception as e:
        print(f"Ein Fehler ist aufgetreten: {e}")
    finally:
        # Sicherstellen, dass die Terminate-Funktion aufgerufen wird
        sim.terminate()
        sim2.terminate()