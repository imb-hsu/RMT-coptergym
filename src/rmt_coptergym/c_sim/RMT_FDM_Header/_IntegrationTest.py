import ctypes
import os

# Importieren der NEUEN, individuellen Bus-Strukturen
from rmt_coptergym.c_code.RMT_structs import (
    Simulation_Control_Bus, States_Init_Bus, fc_pilot_cmd_Bus,
    Vehicle_Bus, Measurements_Bus, fc_est_Bus,
    real_T
)

class InstancedSimulator:
    def __init__(self, lib_path: str):
        if not os.path.exists(lib_path):
            raise FileNotFoundError(f"Bibliothek nicht gefunden unter: {lib_path}")
        
        self.lib = ctypes.CDLL(lib_path)
        print(f"Bibliothek '{lib_path}' erfolgreich geladen.")

        # --- 1. Instanz-spezifische I/O-Strukturen erstellen ---
        # Dies sind die Speicherbereiche, die Python für diese Instanz verwaltet.
        self.sim_control = Simulation_Control_Bus()
        self.states_init = States_Init_Bus()
        self.w_cmd = (real_T * 8)()
        self.pilot_cmd = fc_pilot_cmd_Bus()
        self.vehicle_out = Vehicle_Bus()
        self.measurements_out = Measurements_Bus()
        self.fc_est_out = fc_est_Bus()

        # --- 2. Funktionssignaturen für die neue API definieren ---
        # Die "create"-Funktion, die Pointer auf alle I/O-Strukturen erwartet
        self.lib.RMT_FDM_DLL_FrameWork_FCS.restype = ctypes.c_void_p
        self.lib.RMT_FDM_DLL_FrameWork_FCS.argtypes = [
            ctypes.POINTER(Simulation_Control_Bus),
            ctypes.POINTER(States_Init_Bus),
            ctypes.POINTER(real_T * 8),
            ctypes.POINTER(fc_pilot_cmd_Bus),
            ctypes.POINTER(Vehicle_Bus),
            ctypes.POINTER(Measurements_Bus),
            ctypes.POINTER(fc_est_Bus),
        ]

        # Die `step`-Funktion
        self.lib.RMT_FDM_DLL_FrameWork_FCS_step.argtypes = [
            ctypes.c_void_p,
            ctypes.POINTER(Simulation_Control_Bus),
            ctypes.POINTER(States_Init_Bus),
            ctypes.POINTER(real_T * 8),
            ctypes.POINTER(fc_pilot_cmd_Bus),
            ctypes.POINTER(Vehicle_Bus),
            ctypes.POINTER(Measurements_Bus),
            ctypes.POINTER(fc_est_Bus),
        ]

        # `initialize` und `terminate`
        self.lib.RMT_FDM_DLL_FrameWork_FCS_initialize.argtypes = [ctypes.c_void_p]
        self.lib.RMT_FDM_DLL_FrameWork_FCS_terminate.argtypes = [ctypes.c_void_p]

        # --- 3. Die C-Simulationsinstanz erstellen ("Handle" holen) ---
        # Wir übergeben die Pointer auf unsere Python-verwalteten Strukturen.
        self.handle = self.lib.RMT_FDM_DLL_FrameWork_FCS(
            ctypes.byref(self.sim_control),
            ctypes.byref(self.states_init),
            self.w_cmd,
            ctypes.byref(self.pilot_cmd),
            ctypes.byref(self.vehicle_out),
            ctypes.byref(self.measurements_out),
            ctypes.byref(self.fc_est_out),
        )
        if not self.handle:
            raise RuntimeError("Failed to create simulation instance in C.")
        print(f"C-seitige Simulationsinstanz mit Handle {self.handle} erstellt.")

        # --- 4. Die C-Instanz initialisieren ---
        self.lib.RMT_FDM_DLL_FrameWork_FCS_initialize(self.handle)

    def step(self):
        # Die step-Funktion erwartet bei jedem Aufruf alle I/O-Pointer erneut.
        self.lib.RMT_FDM_DLL_FrameWork_FCS_step(
            self.handle,
            ctypes.byref(self.sim_control),
            ctypes.byref(self.states_init),
            self.w_cmd,
            ctypes.byref(self.pilot_cmd),
            ctypes.byref(self.vehicle_out),
            ctypes.byref(self.measurements_out),
            ctypes.byref(self.fc_est_out),
        )

    def destroy(self):
        if self.handle:
            print(f"Zerstöre C-seitige Instanz mit Handle {self.handle}...")
            self.lib.RMT_FDM_DLL_FrameWork_FCS_terminate(self.handle)
            self.handle = None

    def set_initial_conditions(self, pos_z: float = -10.0):
        # Initialbedingungen werden in die `states_init`-Struktur geschrieben.
        # Diese wird bei jedem `step` an die C-Seite übergeben.
        self.states_init.pos_R_O_m.z_R_O_m = pos_z
        print(f"  [Handle {self.handle}] Start-Position Z gesetzt auf: {pos_z:.4f}")

def set_simulation_run_flags(sim_instance: InstancedSimulator, motor_cmd: float, INDI = False):
    """Helper function to configure all necessary flags for a simulation run step."""
    s_ctrl = sim_instance.sim_control
    s_ctrl.flg_Reset = False
    s_ctrl.flg_Run = True
    s_ctrl.flg_Enable_Controller = False
    s_ctrl.flg_Propulsion_On = True
    s_ctrl.flg_Aerodynamics_On = True
    s_ctrl.flg_Weight_Balance_On = True
    s_ctrl.flg_Run_p = s_ctrl.flg_Run_q = s_ctrl.flg_Run_r = True
    s_ctrl.flg_Run_Phi = s_ctrl.flg_Run_Theta = s_ctrl.flg_Run_Psi = True
    s_ctrl.flg_Run_vel_x = s_ctrl.flg_Run_vel_y = s_ctrl.flg_Run_vel_z = True
    s_ctrl.flg_Run_pos_x = s_ctrl.flg_Run_pos_y = s_ctrl.flg_Run_pos_z = True

    if INDI:
        # Zweiter step() zum Zurücksetzen und Anwenden der Initialwerte

            s_ctrl.flg_Enable_Controller = True

            s_cmd = sim_instance.pilot_cmd
            s_cmd.arm_swi = True
            s_cmd.override_swi = True
            s_cmd.vel_att_mode_swi = True
            s_cmd.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs = -8.0
    else:

        for i in range(8):
            sim_instance.w_cmd[i] = motor_cmd



# =========================================================================
# Hauptlogik mit ALLEN notwendigen Flags
# =========================================================================
if __name__ == "__main__":
    # Pfad zur NEUEN, direkt generierten DLL
    
    library_path = "./RMT_FDM_DLL_FrameWork_FCS.dll"
    sim1, sim2 = None, None
    try:
        print("--- Erstelle und initialisiere Simulatoren ---")
        sim1 = InstancedSimulator(library_path)
        sim1.set_initial_conditions(pos_z=-10.0)
        
        sim2 = InstancedSimulator(library_path)
        sim2.set_initial_conditions(pos_z=-50.0)

        # Ein Reset-Schritt, um die Initialwerte zu übernehmen
        sim1.sim_control.flg_Reset = True
        sim2.sim_control.flg_Reset = True
        sim1.step()
        sim2.step()
        sim1.sim_control.flg_Reset = False
        sim2.sim_control.flg_Reset = False

        print("\n--- Starte parallelen Testlauf ---")
        for i in range(1000):
            set_simulation_run_flags(sim1, motor_cmd=1800.0)
            set_simulation_run_flags(sim2, motor_cmd=00.0, INDI= True )
                
            # Führe den Schritt für beide aus
            sim1.step()
            sim2.step()
            
            # Hole die Positionen
            pos1 = sim1.vehicle_out.States.pos_R_O_m
            pos2 = sim2.vehicle_out.States.pos_R_O_m

            vel1 = sim1.vehicle_out.States.vel_K_R_E_B_mDs
            vel2 = sim2.vehicle_out.States.vel_K_R_E_B_mDs

            print(f"Step {i+1}:")
            print(f"  SIM 1 (Start: -10m, Cmd: 1800): Z={pos1.z_R_O_m:.4f}, VZ={vel1.w_K_R_E_B_mDs:.4f},")
            print(f"  SIM 2 (Start: -50m, Cmd:    0): Z={pos2.z_R_O_m:.4f}, VZ={vel2.w_K_R_E_B_mDs:.4f},")
            
            # Erfolgskriterium: Die Zustände driften auseinander und bewegen sich von ihren Startwerten weg
            states_are_different = abs(pos1.z_R_O_m - pos2.z_R_O_m) > 0.01
            sim1_is_moving = abs(pos1.z_R_O_m - (-10.0)) > 0.001
            sim2_is_moving = abs(pos2.z_R_O_m - (-50.0)) > 0.001 # Sim2 sollte sich ebenfalls bewegen (fallen)

            if states_are_different and sim1_is_moving and sim2_is_moving:
                print("  --> ERFOLG: Zustände sind unterschiedlich UND beide Simulationen laufen!")
            else:
                print("  --> FEHLER: Interferenzen oder Simulation eingefroren.")
            
    except Exception as e:
        import traceback
        print(f"\nEin schwerwiegender Fehler ist aufgetreten: {e}")
        traceback.print_exc()
        
    finally:
        print("\n--- Testlauf beendet, räume auf ---")
        if sim1:
            sim1.destroy()
        if sim2:
            sim2.destroy()