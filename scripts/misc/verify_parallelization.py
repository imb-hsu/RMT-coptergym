import numpy as np
import platform
import matplotlib.pyplot as plt
from functools import partial

from stable_baselines3.common.env_util import make_vec_env
from stable_baselines3.common.vec_env import SubprocVecEnv, DummyVecEnv

# Import your custom environment
from rmt_coptergym.application_envs.RL_VEL_I_Env_relative_WAR import VEL_Env as My_Env

# Schalter für Debug-Ausgaben
DEBUG_PRINT = True
DEBUG_STEPS = 15 # Erhöht, um die Aktionsänderungen zu sehen

def create_manual_dataset():
    """Erstellt ein Dummy-Dataset, um die Env zu initialisieren."""
    return {
        'time': np.array([[0.0, 10.0]]), 'pos': np.array([[[0, 0, -10], [0, 0, -10]]]),
        'vel': np.array([[[0, 0, 0], [0, 0, 0]]]), 'vel_limit': np.array([[[5, 5, 5], [5, 5, 5]]]),
        'rpy': np.array([[[0, 0, 0], [0, 0, 0]]]), 'thrust': np.array([[823.0, 823.0]])
    }

def run_and_collect_data(env, initial_actions, num_steps=100):
    """
    Führt eine Episode mit einer dynamischen Aktionssequenz für beide Umgebungen aus.
    """
    obs = env.reset()
    log_data_env1 = []
    log_data_env2 = []
    
    # Definiere die verschiedenen Aktionen
    action_env1_initial, action_env2_initial = initial_actions
    zero_action = np.zeros(8)
    strong_action = np.ones(8) # Entspricht dem Maximalwert im Action Space
    minus_action = -1*np.ones(8)

    for i in range(num_steps):
        # Dynamische Aktionssequenz
        if i < 10:
            actions = [action_env1_initial, action_env2_initial]
        elif i < 120:
            actions = [zero_action, minus_action]
        else:
            actions = [zero_action, strong_action]

        obs, _, _, infos = env.step(actions)
        
        # Daten für jede Umgebung separat speichern
        log_data_env1.append(infos[0])
        log_data_env2.append(infos[1])
        
        # Debug-Ausgabe, die beide Umgebungen zeigt
        if DEBUG_PRINT and i < DEBUG_STEPS:
            print(f"[DEBUG] Step {i+1:04d} | ENV1 Time: {infos[0]['sim_time']:.3f}s | ENV2 Time: {infos[1]['sim_time']:.3f}s | "
                  f"ENV1 Pos Z: {infos[0]['agent_pos'][2]:.2f} | ENV2 Pos Z: {infos[1]['agent_pos'][2]:.2f}")

    return log_data_env1, log_data_env2

def make_env(env_class, **kwargs):
    """Hilfsfunktion zur Erstellung einer einzelnen Umgebung."""
    return env_class(**kwargs)

def main():
    """Hauptfunktion zum Testen der echten Parallelisierbarkeit innerhalb einer VecEnv."""
    print("--- Starting True Parallelization Verification Test ---")
    
    NUM_SIM_STEPS = 250 # Gekürzt, um die dynamische Sequenz besser zu sehen
    print(f"Running simulation for {NUM_SIM_STEPS} steps (approx. {NUM_SIM_STEPS/125.0:.2f} seconds @ 125Hz).")

    # --- 1. Definition der Aktionen und Anomalien ---
    action_env2 = np.array([0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5])
    anomaly_env2 = {'time': np.array([None, None]), 'performance_loss': np.zeros(8)}

    #action_env2 = np.array([-0.025, -0.025, 0.025, 0.025, -0.025, -0.025, 0.025, 0.025])
    action_env1 = -1*np.ones(8)
    anomaly_env1 = {'time': np.array([None, None]), 'performance_loss': np.full(8, 0.20)}
    
    initial_actions = [action_env2, action_env1]

    # --- 2. Einrichten EINER Vektor-Umgebung mit ZWEI parallelen Prozessen ---
    dummy_dataset = create_manual_dataset()
    
    # Erstelle separate Konfigurationen für jede Umgebung
    env1_kwargs = {'dataset': dummy_dataset, 'is_eval': False, 'use_unix': platform.system() != "Windows", 'anomaly': anomaly_env1, 'seed': 42}
    env2_kwargs = {'dataset': dummy_dataset, 'is_eval': False, 'use_unix': platform.system() != "Windows", 'anomaly': anomaly_env2, 'seed': 1337}

    # Erstelle eine Liste von Funktionen, die jeweils eine Umgebung mit der spezifischen Konfiguration erstellen
    env_creators = [
        partial(make_env, My_Env, **env1_kwargs),
        partial(make_env, My_Env, **env2_kwargs)
    ]
    
    # Wähle den VecEnv-Typ. SubprocVecEnv für echte Parallelität, DummyVecEnv für sequentielles Debugging.
    VecEnvClass = SubprocVecEnv if platform.system() != "Windows" else DummyVecEnv
    # Hinweis: SubprocVecEnv erfordert den `if __name__ == '__main__':` Schutz.
    
    vec_env = VecEnvClass(env_creators)


    # --- 3. Experimente durchführen und Daten sammeln ---
    print("\n--- Running First Pass (Run 1) ---")
    run1_env1_data, run1_env2_data = run_and_collect_data(vec_env, initial_actions, NUM_SIM_STEPS)

    print("\n--- Resetting Environment and Running Second Pass (Run 2) ---")
    run2_env1_data, run2_env2_data = run_and_collect_data(vec_env, initial_actions, NUM_SIM_STEPS)

    vec_env.close()

    # --- 4. Plotten zur Verifizierung (Struktur unverändert, nur Datenquellen sind neu) ---
    print("\n--- Generating Plots for Verification ---")
    fig, axes = plt.subplots(4, 2, figsize=(20, 22), sharex=True)
    fig.suptitle("True Parallelization Verification: State Trajectories within one VecEnv", fontsize=16)

    def get_trajectory(data, key):
        return np.array([d.get(key, np.nan) for d in data])

    # Plotting-Code ist identisch, da die Datenvariablen gleich benannt sind.
    # --- Plots für Environment 1 ---
    axes[0, 0].set_title("ENV 1 (Sideways -> Zero): Position")
    axes[0, 0].plot(get_trajectory(run1_env1_data, 'agent_pos')[:, 0], label='Run 1 - X', c='blue', ls='-')
    axes[0, 0].plot(get_trajectory(run2_env1_data, 'agent_pos')[:, 0], label='Run 2 - X', c='cyan', ls='--')
    axes[0, 0].plot(get_trajectory(run1_env1_data, 'agent_pos')[:, 1], label='Run 1 - Y', c='red', ls='-')
    axes[0, 0].plot(get_trajectory(run2_env1_data, 'agent_pos')[:, 1], label='Run 2 - Y', c='magenta', ls='--')
    axes[0, 0].plot(get_trajectory(run1_env1_data, 'agent_pos')[:, 2], label='Run 1 - Z', c='darkgreen', ls='-')
    axes[0, 0].plot(get_trajectory(run2_env1_data, 'agent_pos')[:, 2], label='Run 2 - Z', c='lightgreen', ls='--')
    axes[0, 0].legend(); axes[0, 0].grid(True); axes[0, 0].set_ylabel("Position [m]")

    axes[1, 0].set_title("ENV 1: Velocity")
    axes[1, 0].plot(get_trajectory(run1_env1_data, 'agent_vel_c')[:, 0], label='Run 1 - Vel X', c='blue', ls='-')
    axes[1, 0].plot(get_trajectory(run2_env1_data, 'agent_vel_c')[:, 0], label='Run 2 - Vel X', c='cyan', ls='--')
    axes[1, 0].plot(get_trajectory(run1_env1_data, 'agent_vel_c')[:, 1], label='Run 1 - Vel Y', c='red', ls='-')
    axes[1, 0].plot(get_trajectory(run2_env1_data, 'agent_vel_c')[:, 1], label='Run 2 - Vel Y', c='magenta', ls='--')
    axes[1, 0].legend(); axes[1, 0].grid(True); axes[1, 0].set_ylabel("Velocity [m/s]")

    axes[2, 0].set_title("ENV 1: RPY Angles")
    axes[2, 0].plot(get_trajectory(run1_env1_data, 'agent_rpy_deg')[:, 0], label='Run 1 - Roll', c='red', ls='-')
    axes[2, 0].plot(get_trajectory(run2_env1_data, 'agent_rpy_deg')[:, 0], label='Run 2 - Roll', c='red', ls='--', alpha=0.7)
    axes[2, 0].plot(get_trajectory(run1_env1_data, 'agent_rpy_deg')[:, 1], label='Run 1 - Pitch', c='green', ls='-')
    axes[2, 0].plot(get_trajectory(run2_env1_data, 'agent_rpy_deg')[:, 1], label='Run 2 - Pitch', c='green', ls='--', alpha=0.7)
    axes[2, 0].legend(); axes[2, 0].grid(True); axes[2, 0].set_ylabel("Angle [deg]")
    
    axes[3, 0].set_title("ENV 1: All Motor RPS (Measured)")
    for i in range(8):
        #axes[3, 0].plot(get_trajectory(run1_env1_data, 'motor_signal_measured_rps')[:, i], label=f'M{i+1} Run 1', alpha=0.8)
        #axes[3, 0].plot(get_trajectory(run2_env1_data, 'motor_signal_measured_rps')[:, i], label=f'M{i+1} Run 2', ls='--', alpha=0.6)
        axes[3, 0].plot(get_trajectory(run2_env1_data, 'motor_cmds_setpoint_rps')[:, i], label=f'M{i+1} Run 2', ls=':', alpha=1)
    axes[3, 0].legend()
    axes[3, 0].grid(True); axes[3, 0].set_ylabel("RPS"); axes[3, 0].set_xlabel("Steps")

    # --- Plots für Environment 2 ---
    axes[0, 1].set_title("ENV 2 (Forward -> Zero -> Strong): Position")
    axes[0, 1].plot(get_trajectory(run1_env2_data, 'agent_pos')[:, 0], label='Run 1 - X', c='blue', ls='-')
    axes[0, 1].plot(get_trajectory(run2_env2_data, 'agent_pos')[:, 0], label='Run 2 - X', c='cyan', ls='--')
    axes[0, 1].plot(get_trajectory(run1_env2_data, 'agent_pos')[:, 1], label='Run 1 - Y', c='red', ls='-')
    axes[0, 1].plot(get_trajectory(run2_env2_data, 'agent_pos')[:, 1], label='Run 2 - Y', c='magenta', ls='--')
    axes[0, 1].plot(get_trajectory(run1_env2_data, 'agent_pos')[:, 2], label='Run 1 - Z', c='darkgreen', ls='-')
    axes[0, 1].plot(get_trajectory(run2_env2_data, 'agent_pos')[:, 2], label='Run 2 - Z', c='lightgreen', ls='--')
    axes[0, 1].legend(); axes[0, 1].grid(True)

    axes[1, 1].set_title("ENV 2: Velocity")
    axes[1, 1].plot(get_trajectory(run1_env2_data, 'agent_vel_c')[:, 0], label='Run 1 - Vel X', c='blue', ls='-')
    axes[1, 1].plot(get_trajectory(run2_env2_data, 'agent_vel_c')[:, 0], label='Run 2 - Vel X', c='cyan', ls='--')
    axes[1, 1].plot(get_trajectory(run1_env2_data, 'agent_vel_c')[:, 1], label='Run 1 - Vel Y', c='red', ls='-')
    axes[1, 1].plot(get_trajectory(run2_env2_data, 'agent_vel_c')[:, 1], label='Run 2 - Vel Y', c='magenta', ls='--')
    axes[1, 1].legend(); axes[1, 1].grid(True)
    
    axes[2, 1].set_title("ENV 2: RPY Angles")
    axes[2, 1].plot(get_trajectory(run1_env2_data, 'agent_rpy_deg')[:, 0], label='Run 1 - Roll', c='red', ls='-')
    axes[2, 1].plot(get_trajectory(run2_env2_data, 'agent_rpy_deg')[:, 0], label='Run 2 - Roll', c='red', ls='--', alpha=0.7)
    axes[2, 1].plot(get_trajectory(run1_env2_data, 'agent_rpy_deg')[:, 1], label='Run 1 - Pitch', c='green', ls='-')
    axes[2, 1].plot(get_trajectory(run2_env2_data, 'agent_rpy_deg')[:, 1], label='Run 2 - Pitch', c='green', ls='--', alpha=0.7)
    axes[2, 1].legend(); axes[2, 1].grid(True)
    
    axes[3, 1].set_title("ENV 2: All Motor RPS (Measured)")
    for i in range(8):
        #axes[3, 1].plot(get_trajectory(run1_env2_data, 'motor_signal_measured_rps')[:, i], label=f'M{i+1} Run 1', alpha=0.8)
        #axes[3, 1].plot(get_trajectory(run2_env2_data, 'motor_signal_measured_rps')[:, i], label=f'M{i+1} Run 2', ls='--', alpha=0.6)
        axes[3, 1].plot(get_trajectory(run2_env2_data, 'motor_cmds_setpoint_rps')[:, i], label=f'M{i+1} Run 2', ls=':', alpha=1)

    axes[3, 1].legend()
    axes[3, 1].grid(True); axes[3, 1].set_ylabel("RPS"); axes[3, 1].set_xlabel("Steps")

    plt.tight_layout(rect=[0, 0.03, 1, 0.97])
    plt.savefig("parallelization_verification.png")
    print("\nVerification plot saved to 'parallelization_verification.png'")
    plt.show()

if __name__ == '__main__':
    main()