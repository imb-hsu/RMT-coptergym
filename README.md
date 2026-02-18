# RL-CopterBase
Backup for RL-Testbed for differnet Copter Teststudies - Currently private Version for use at HSU --> aimed to be published

This repository serves as a research testbed for comparing drone control strategies, with a focus on Reinforcement Learning. The primary goal is to provide a modular framework for evaluating different RL controllers against classical, model-based approaches within a consistent simulation environment.


The project uses `stable-baselines3` for RL training, focusing on the PPO algorithm, while supporting `Box` and `MultiDiscrete` (for simple Action masking tasks with `MaskedPPO`) action spaces. The simulation is performed by running a MATLAB/Simulink model exported as a C-shared library (`.dll` for Windows, `.so` for Linux). This allows for fast and accurate physics simulation outside of the MATLAB environment. To use the internal MATLAB/Simulink simulation structsthe default C-header is conferted to a refernce of python classes.

Current Status of use:
- Windows .dll files : is working but not tested in detail
- Linux .so files: is recommended to use

File Structure:
```
.
├── RMT/
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
│   # Stores generated mission datasets (*.npz files).
│
├── scripts/
│   # Main entry points for training, data generation, and analysis.
│   ├── train.py
│   ├── generate_structured_dataset.py
│   └── analysis.ipynb
│
├── saves/
│   # Default directory for saving trained model checkpoints and logs.
│
├── old/
│   # Archived legacy code for reference.
│
├── pybullet-drones/
│   # Git submodule for future physics engine comparison.
│
├── install.sh              # Installation script for dependencies.
├── todo-list.md            # Development planning and research notes.
└── README.md               # Project overview and documentation.
```

Comparison of Simulation with pybullet-drones will be investigated in the future:
Current Status:
- Same Plot/Data Output:        not done
- Custom Wrapper Env:           not done
- Integration in Train-Scripts: not done
- uniform evaluation            not done

------

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

> Dont forget the extension in VS Code!

## WINDOWS 11 Setup

You can use the prepared powerscript file to install all dependencies as in Linux, but keep in mind to have Anaconda or miniconda installed.
Miniconda should work but is currently not well tested.
 
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
Afterwards restart your PowerShell. This updates your $PROFILE to make conda accessible.

Once Conda is setup use the powershell install script to install teh packages, otherwise refer to the manual installation process from linux and install the same packages/dependencies - all should work for both operating systems.


## Setup for Visual Studio Code

In VS Code, you can select the Conda environment automatically:
>Ctrl+Shift+P → Python: Select Interpreter

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
