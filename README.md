# RMT-coptergym

This repository serves as a research testbed for comparing drone control strategies for X8 coaxial multicopters, with a focus on Reinforcement Learning. The primary goal is to provide a modular framework for evaluating different RL controllers against classical, model-based approaches within a consistent simulation environment.

## Table of Contents
- [Project Description](#project-description)
- [Internal Usage](#internal-usage)
- [Package Structure: rmt_coptergym](#package-structure-rmt_coptergym)
  - [Data Structures & C-Interface](#data-structures--c-interface)
  - [Simulation Architecture](#simulation-architecture)
- [INIT and INSTALL](#init-and-install)
  - [LINUX Setup](#linux-setup)
  - [WINDOWS 11 Setup](#windows-11-setup)
  - [Setup for Visual Studio Code](#setup-for-visual-studio-code)
- [Citation](#citation)

---

## Project Description
RMT-coptergym provides a high-fidelity Gymnasium-based environment for the development and benchmarking of flight control laws on coaxial X8 multicopters. It is specifically designed to facilitate research in **Fault-Tolerant Control (FTC)** and **Reinforcement Learning (RL)**.

The environment uses `stable-baselines3` for training, primarily utilizing the PPO algorithm with continuous `Box` action spaces. The simulation is powered by a MATLAB/Simulink model exported as a C-shared library (`.dll` or `.so`), allowing for high-performance physics calculations without requiring a MATLAB license at runtime. 
Additionally, our training scripts support parallel instances via `SubprocVecEnv`, enabling the simultaneous training of multiple systems with their own randomized seeds.

## Internal Usage
This framework is used internally to evaluate the robustness of RL agents against classical control laws like INDI (Incremental Nonlinear Dynamic Inversion). It supports complex mission profiles (Velocity/Position tracking) and the injection of actuator anomalies, such as Loss of Effectiveness (LoE) or complete motor dropouts, to test adaptive and fault-tolerant behaviors.

## Package Structure: rmt_coptergym

The code is organized as a standard Python package located in the `src/` directory. This allows for clean imports and modularity.

### Folder Overview
```
.
├── src/rmt_coptergym/
│   # Core module containing the simulation and Gymnasium environments.
│   ├── RMT_structs.py
│   └── gym_env/
│       # Contains all custom Gymnasium environment classes.
│       ├── RMT_Base_Env.py, ...
│       └── utils/
│           # Helper modules, e.g., for mission management.
│           └── mission_manager.py
│
├── data/
│   # Stores generated mission datasets and evaluation files.
│
├── scripts/
│   # Main entry points for training, data generation, and analysis.
│   ├── train.py
│   ├── generate_csv_dataset.py
│   └── analysis.ipynb
│
├── saves/
│   # Default directory for saving trained model checkpoints and logs.
│
├── old/
│   # Archived legacy code for reference.
│
├── install.sh              # Installation script for dependencies.
├── todo-list.md            # Development planning and research notes.
└── README.md               # Project overview and documentation.
```

The core logic is located in the `src/rmt_coptergym` directory:

- `base_envs/`: Contains `RMT_Base_Env.py`, the foundation for all simulation environments.
- `application_envs/`: Specific RL environment implementations (e.g., velocity tracking, PID-based rewards).
- `c_sim/`: Contains the C-library wrappers and data structure definitions.
- `utils/`: Utilities for mission management, trajectory loading, and visualization.

### Data Structures & C-Interface
- **Simulation**: Fast, accurate physics .
To maintain compatibility with the Simulink bus structures used in the C-libraries, the project uses `ctypes` to map C-structs to Python classes. These are defined in:
`src/rmt_coptergym/c_sim/RMT_structs.py`

The c-files are compiled and used as libraries:
- **Linux (.so)**: Recommended for training on servers.
- **Windows (.dll)**: Functional, but no in depth tested.

This file acts as the bridge, ensuring that Python can correctly read and write to the memory used by the compiled simulation library.
 It defines all inputs (commands, state initialization) and outputs (vehicle states, sensor measurements).

### Simulation Architecture
The simulation lifecycle is managed within `src/rmt_coptergym/base_envs/RMT_Base_Env.py`. This class performs the following tasks:
1. **DLL/SO Loading**: Dynamically loads the shared library based on the operating system.
2. **Instance Handling**: Manages pointers to the C-structures and calls the simulation `step` function at a fixed frequency (default 250 Hz).
3. **Simulation Control**: Handles the transition between simulation resets and active runs, including "settling" steps to allow derivative blocks to converge.
4. **Transformation**: Maps raw simulation data to the Gymnasium observation and action spaces.
5. **Logging**: Creates the info dictionaries to track internal behaviour and invisible states

---


# INIT and INSTALL

For the installation process we refer to the setup for Linux, Windows and Visual Studio Code. The last one is not essential but for anyone starting of we included usefull plugins to be set up with this simulation environment.

The installation of thes eplugins is optional and the install-scripts ask beforehand if an installations is desired or should be skipped. 

## LINUX Setup
Designed to use for our Server (running Ubuntu 22.04.3 LTS), but should work outside too.
Recommended to use the install script via:
```
chmod +x install.sh
./install.sh
```
> If you use the *install.sh* you don't need the manual setup

At the end of the install script, you will be prompted to install Visual Studio Code extensions; this is optional and can be skipped.

### Manual Setup for VS Code or other Normal editing
```
conda init zsh 
source ~/.zshrc
conda create --prefix ~/.venv python=3.11
conda activate ~/.venv

pip install 'stable-baselines3[extra]'
pip install sb3-contrib
```
to run teh conda env and activation
```
conda init zsh 
source ~/.zshrc
conda activate ~/.venv
```

It is also recommended to change the upper level of bashrc to init zsh and activate passively
```
sed -i 's|conda activate base|conda activate ~/venv|' "$BASHRC_PATH"
```


### Manual Setup for Jupyter Notebook

```
conda create --prefix ~/.venv python=3.9
conda activate ~/.venv

conda install ipykernel
ipython kernel install --prefix=/home/jovyan/.venv --name my_kernel --display-name 'my_kernel'   
```


## WINDOWS 11 Setup

You can use the prepared powerscript file to install all dependencies as in Linux, but keep in mind to have Anaconda installed. (Miniconda should work but is currently not tested)
 
### How to setup Conda after Install
Check if `conda --version` is recognized.

Otherwise, add to `$PROFILE`:
echo $PROFILE
notebook $PROFILE

```
# >>> conda initialize >>>
(& "$env:USERPROFILE\anaconda3\shell\condabin\conda-hook.ps1")
# <<< conda initialize <<<
```

In PowerShell:
```
& "$env:USERPROFILE\anaconda3\Scripts\conda.exe" init powershell
```
Afterward, restart your PowerShell. This updates your `$PROFILE` to make conda accessible.

Once Conda is set up, use the PowerShell install script or follow the manual installation process—dependencies are consistent across platforms.


## Setup for Visual Studio Code

In VS Code, you can select the Conda environment automatically:
> `Ctrl+Shift+P` → `Python: Select Interpreter`
> if in server mode the shortcut is not avaialble - locate the settinsg via `View` → `Command palette` 

Select your Conda environment there.
Then VS Code will open the terminal directly in this environment, without you having to manually call `conda activate`.
This way, you don't need to perform an extra subfolder activation in the terminal.
Alternatively, you can set a global setting for `settings.json`
```
"python.condaPath": "C:/Users/USERNAME/miniconda3/Scripts/conda.exe"
```
or
```
"python.defaultInterpreterPath":  "C:\\Users\\USERNAME\\anaconda3\\envs\\rmt\\python.exe"
```

Then VS Code will automatically recognize your Conda environments.


## Citation

The paper was presented at the 9th ICPS Conference in Pert, Australia. Once the conference proceedings are published this section will be updated.