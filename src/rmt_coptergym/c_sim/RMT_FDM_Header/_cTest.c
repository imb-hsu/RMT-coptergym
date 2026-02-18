#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "RMT_FDM_DLL_FrameWork_FCS.h" // The new header from Simulink

int main() {
    const char *library_path = "RMT_FDM_DLL_FrameWork_FCS.dll"; // The new reentrant DLL
    HMODULE lib_handle = LoadLibrary(library_path);
    if (!lib_handle) {
        fprintf(stderr, "Error loading library: %lu\n", GetLastError());
        return 1;
    }

    // Define function pointers for the NEW reentrant API from the generated code
    RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T* (*model_create_func)(Simulation_Control_Bus *, States_Init_Bus *, real_T[8], fc_pilot_cmd_Bus *,
                                                             Vehicle_Bus *, Measurements_Bus *, fc_est_Bus *);

    void (*model_step_func)(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T *const,
                            Simulation_Control_Bus *, States_Init_Bus *, real_T[8], fc_pilot_cmd_Bus *,
                            Vehicle_Bus *, Measurements_Bus *, fc_est_Bus *);
    void (*model_initialize_func)(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T *const);
    void (*model_terminate_func)(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T *const);

    // Load the new functions
    // The main model function acts as the "create" function
    model_create_func = (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T* (*)(Simulation_Control_Bus *, States_Init_Bus *, real_T[8], fc_pilot_cmd_Bus *,
                                                                  Vehicle_Bus *, Measurements_Bus *, fc_est_Bus *)) GetProcAddress(lib_handle, "RMT_FDM_DLL_FrameWork_FCS");

    model_step_func = (void (*)(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T *const,
                                Simulation_Control_Bus *, States_Init_Bus *, real_T[8], fc_pilot_cmd_Bus *,
                                Vehicle_Bus *, Measurements_Bus *, fc_est_Bus *)) GetProcAddress(lib_handle, "RMT_FDM_DLL_FrameWork_FCS_step");
    model_initialize_func = (void (*)(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T *const)) GetProcAddress(lib_handle, "RMT_FDM_DLL_FrameWork_FCS_initialize");
    model_terminate_func = (void (*)(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T *const)) GetProcAddress(lib_handle, "RMT_FDM_DLL_FrameWork_FCS_terminate");

    // Add error checking for GetProcAddress calls...

    printf("Creating two simulation instances...\n");

    // === INSTANCE 1 ===
    Simulation_Control_Bus sim1_sim_control = {0};
    States_Init_Bus sim1_states_init = {0};
    real_T sim1_w_cmd[8] = {0};
    fc_pilot_cmd_Bus sim1_pilot_cmd = {0};
    Vehicle_Bus sim1_vehicle_out = {0};
    Measurements_Bus sim1_measurements_out = {0};
    fc_est_Bus sim1_fc_est_out = {0};

    // Create the handle by passing pointers to the I/O structs
    RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T* sim1_handle = model_create_func(&sim1_sim_control, &sim1_states_init, sim1_w_cmd, &sim1_pilot_cmd,
                                                                        &sim1_vehicle_out, &sim1_measurements_out, &sim1_fc_est_out);

    model_initialize_func(sim1_handle);
    // Set initial conditions for sim1
    sim1_states_init.pos_R_O_m.z_R_O_m = -10.0;

    // === INSTANCE 2 ===
    Simulation_Control_Bus sim2_sim_control = {0};
    States_Init_Bus sim2_states_init = {0};
    real_T sim2_w_cmd[8] = {0};
    fc_pilot_cmd_Bus sim2_pilot_cmd = {0};
    Vehicle_Bus sim2_vehicle_out = {0};
    Measurements_Bus sim2_measurements_out = {0};
    fc_est_Bus sim2_fc_est_out = {0};

    // Create the handle by passing pointers to the I/O structs
    RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_T* sim2_handle = model_create_func(&sim2_sim_control, &sim2_states_init, sim2_w_cmd, &sim2_pilot_cmd,
                                                                        &sim2_vehicle_out, &sim2_measurements_out, &sim2_fc_est_out);

    model_initialize_func(sim2_handle);
    // Set initial conditions for sim2
    sim2_states_init.pos_R_O_m.z_R_O_m = -50.0;

    printf("Running parallel steps...\n");
    for (int i = 0; i < 100; i++) {
        // --- Set inputs for this step ---
        // Enable all physics and integration flags for sim1
        sim1_sim_control.flg_Run = (boolean_T)true;
        sim1_sim_control.flg_Reset = (boolean_T)false;
        sim1_sim_control.flg_Enable_Controller = (boolean_T)false; // Use direct motor commands
        sim1_sim_control.flg_Propulsion_On = (boolean_T)true;
        sim1_sim_control.flg_Aerodynamics_On = (boolean_T)true;
        sim1_sim_control.flg_Weight_Balance_On = (boolean_T)true;
        sim1_sim_control.flg_Run_p = sim1_sim_control.flg_Run_q = sim1_sim_control.flg_Run_r = (boolean_T)true;
        sim1_sim_control.flg_Run_Phi = sim1_sim_control.flg_Run_Theta = sim1_sim_control.flg_Run_Psi = (boolean_T)true;
        sim1_sim_control.flg_Run_vel_x = sim1_sim_control.flg_Run_vel_y = sim1_sim_control.flg_Run_vel_z = (boolean_T)true;
        sim1_sim_control.flg_Run_pos_x = sim1_sim_control.flg_Run_pos_y = sim1_sim_control.flg_Run_pos_z = (boolean_T)true;
        for (int j = 0; j < 8; j++) sim1_w_cmd[j] = 1800.0;

        // Enable all physics and integration flags for sim2
        sim2_sim_control.flg_Run = (boolean_T)true;
        sim2_sim_control.flg_Reset = (boolean_T)false;
        sim2_sim_control.flg_Enable_Controller = (boolean_T)false; // Use direct motor commands
        sim2_sim_control.flg_Propulsion_On = (boolean_T)true;
        sim2_sim_control.flg_Aerodynamics_On = (boolean_T)true;
        sim2_sim_control.flg_Weight_Balance_On = (boolean_T)true;
        sim2_sim_control.flg_Run_p = sim2_sim_control.flg_Run_q = sim2_sim_control.flg_Run_r = (boolean_T)true;
        sim2_sim_control.flg_Run_Phi = sim2_sim_control.flg_Run_Theta = sim2_sim_control.flg_Run_Psi = (boolean_T)true;
        sim2_sim_control.flg_Run_vel_x = sim2_sim_control.flg_Run_vel_y = sim2_sim_control.flg_Run_vel_z = (boolean_T)true;
        sim2_sim_control.flg_Run_pos_x = sim2_sim_control.flg_Run_pos_y = sim2_sim_control.flg_Run_pos_z = (boolean_T)true;
        for (int j = 0; j < 8; j++) sim2_w_cmd[j] = 0.0;

        // --- Step both simulations ---
        // Note how we pass the handle, and then pointers to all I/O structs
        model_step_func(sim1_handle,
                        &sim1_sim_control, &sim1_states_init, sim1_w_cmd, &sim1_pilot_cmd,
                        &sim1_vehicle_out, &sim1_measurements_out, &sim1_fc_est_out);

        model_step_func(sim2_handle,
                        &sim2_sim_control, &sim2_states_init, sim2_w_cmd, &sim2_pilot_cmd,
                        &sim2_vehicle_out, &sim2_measurements_out, &sim2_fc_est_out);

        // --- Print results ---
        // The output data is now in our local output structs
        printf("Step %d:\n", i + 1);
        printf("  Sim 1 Z-Pos: %f\n", sim1_vehicle_out.States.pos_R_O_m.z_R_O_m);
        printf("  Sim 2 Z-Pos: %f\n", sim2_vehicle_out.States.pos_R_O_m.z_R_O_m);
    }

    // === Clean up ===
    model_terminate_func(sim1_handle);
    model_terminate_func(sim2_handle);
    FreeLibrary(lib_handle);

    return 0;
}
