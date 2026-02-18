#!/bin/bash

# --- Script Execution Instructions ---
# chmod +x install.sh
# ./install.sh

# --- Script Configuration and Best Practices ---
# Exit immediately if a command exits with a non-zero status.
set -e
# Treat unset variables as an error when substituting.
set -u

# --- Directory Setup ---
CUR_DIR="$(pwd)"
CACHE_DIR="$CUR_DIR/tmp_pip_cache"
VENV_PATH="$HOME/venv/rmt"

# Create necessary directories
mkdir -p "$CACHE_DIR"
mkdir -p "$CUR_DIR/saves"

# --- Conda Initialization ---
# Initialize Conda for bash and zsh shells, redirect output to hide it.
conda init bash > /dev/null 2>&1 || true
conda init zsh > /dev/null 2>&1 || true

# Make the 'conda' shell function available to this script.
eval "$(conda shell.bash hook)"

# --- Conda Environment Creation ---
# Check if the environment already exists.
if [ -d "$VENV_PATH" ]; then
    echo "Warning: The Conda environment '$VENV_PATH' already exists."
    read -p "Do you want to delete it and create a new one? (y/n): " recreate_env
    # **BUG FIX**: Added 'y' and 'yes' to the condition.
    if [[ "${recreate_env,,}" == "j" || "${recreate_env,,}" == "ja" || "${recreate_env,,}" == "y" || "${recreate_env,,}" == "yes" ]]; then
        echo "Deleting existing environment..."
        # Temporarily disable 'set -u' for the potentially faulty conda deactivate script
        set +u
        conda deactivate || true # Deactivate if active
        set -u
        rm -rf "$VENV_PATH"
        echo "Creating new Conda environment..."
        conda create --prefix "$VENV_PATH" python=3.11 -y
    else
        echo "Using existing environment."
    fi
else
    echo "Creating new Conda environment at '$VENV_PATH'..."
    conda create --prefix "$VENV_PATH" python=3.11 -y
fi


# --- Environment Activation and Package Installation ---
echo "Activating the Conda environment..."
eval "$(conda shell.bash hook)" 
set +u
conda activate "$VENV_PATH"
set -u

echo "Installing compiler via Conda..."
# Temporarily disable 'set -u' because Conda's post-install scripts can be faulty on some systems
set +u
conda install -c conda-forge gcc_linux-64 gxx_linux-64 -y
conda install -c conda-forge make -y
# Re-enable 'set -u' for the rest of the script
set -u

echo "Installing all Python packages via pip from requirements.txt..."
pip install -r requirements.txt || { echo "ERROR: Failed to install packages from requirements.txt"; exit 1; }

echo "Installing the local RMT environment package in editable mode..."
pip install -e . || { echo "ERROR: Failed to install the local RMT package"; exit 1; }

echo "Registering Jupyter kernel..."
python -m ipykernel install --user --name venv_kernel --display-name "Python (rmt-venv)" || { echo "ERROR: Failed to configure the Jupyter kernel"; exit 1; }

# --- Configure .bashrc for alias and auto-activation ---
echo "Customizing .bashrc for automatic activation and compiler alias..."
BASHRC_PATH="$HOME/.bashrc"

# Find the full path to the new compiler
COMPILER_PATH=$(find "$VENV_PATH/bin" -name "*-conda-linux-gnu-gcc")

if [ -z "$COMPILER_PATH" ]; then
    echo "ERROR: Conda GCC compiler not found after installation."
    exit 1
fi

echo "Compiler found at: $COMPILER_PATH. Now updating .bashrc..."
# Create .bashrc if it doesn't exist
touch "$BASHRC_PATH"
# Create a backup of the original .bashrc file
cp "$BASHRC_PATH" "$BASHRC_PATH.bak"
echo "Backup of .bashrc created at: $BASHRC_PATH.bak"

# Define markers for the configuration block
START_MARKER="# === Configuration for RMT-FDM Project ==="
END_MARKER="# === End of RMT-FDM Configuration ==="

# Remove the old configuration block if it exists
sed -i "/$START_MARKER/,/$END_MARKER/d" "$BASHRC_PATH"
echo "Removed old configuration block (if any)."

# Create the new configuration block using a Here Document
CONFIG_BLOCK=$(cat <<EOL
$START_MARKER
# Automatically activate the Conda environment for new terminals
conda activate $VENV_PATH

# Alias for the project-specific Conda C compiler
alias gcc='$COMPILER_PATH'
$END_MARKER
EOL
)

# Append the new block to the end of .bashrc
echo "$CONFIG_BLOCK" >> "$BASHRC_PATH"
echo ".bashrc was successfully updated."

# --- User prompt for VS Code Extensions ---
read -p "Do you want to install VS Code extensions (for Jupyter and Python)? (y/n): " install_vsc
install_vsc=${install_vsc,,}  # to lowercase

if [[ "$install_vsc" == "j" || "$install_vsc" == "ja" || "$install_vsc" == "y" || "$install_vsc" == "yes" ]]; then

    # --- Find the correct command for VS Code ---
    if command -v code-server &> /dev/null; then
        VSC_CMD="code-server"
    elif command -v code &> /dev/null; then
        VSC_CMD="code"
    else
        echo "ERROR: Neither 'code' nor 'code-server' command found. Cannot install extensions."
        exit 1
    fi

    # --- List of extensions to install ---
    EXTENSIONS=(
        ms-python.python                    # for python support
        ms-toolsai.jupyter                  # for jupyter notebooks
        ms-toolsai.jupyter-keymap           # probably installed with jupyter extension 
        ms-toolsai.jupyter-renderers        # probably installed with jupyter extension 
        ms-vscode.cpptools-extension-pack   # for C/C++ support
        GitHub.vscode-pull-request-github   # for Pull Requests, Issues, etc.
        eamodio.gitlens                     # for advanced Git history and blame information
        repreng.csv                         # tabular view for csv with colour code
    )

    echo "Installing extensions via $VSC_CMD..."

    for ext in "${EXTENSIONS[@]}"; do
        # Use -i for case-insensitive grep
        if ! $VSC_CMD --list-extensions | grep -qi "$ext"; then
            echo "-> Installing $ext"
            $VSC_CMD --install-extension "$ext"
        else
            echo "-> $ext is already installed."
        fi
    done

else
    echo "Skipping installation of VS Code extensions."
fi

echo -e "\nSetup finished successfully. Please restart your terminal or run 'source ~/.bashrc' to apply the changes also restart VS Code and follow the instructions in README.md to select the python interpreter."
