param(
    [string]$EnvName = "rmt",
    [string]$PythonVersion = "3.11"
)

# --- Check Conda Installation ---
Write-Host "Checking Conda installation..."
if (-not (Get-Command conda -ErrorAction SilentlyContinue)) {
    Write-Error "Conda not found. Please install Anaconda or Miniconda and ensure it's in your PATH."
    exit 1
}

# --- Prepare Directories ---
$CUR_DIR   = Get-Location
$CACHE_DIR = Join-Path $CUR_DIR "tmp_pip_cache"
$SAVE_DIR  = Join-Path $CUR_DIR "saves"
New-Item -ItemType Directory -Force -Path $CACHE_DIR | Out-Null
New-Item -ItemType Directory -Force -Path $SAVE_DIR  | Out-Null

# --- Create Conda Environment ---
Write-Host "Checking if environment '$EnvName' exists..."
$envExists = conda env list | Select-String "^\s*$EnvName\s"
if (-not $envExists) {
    Write-Host "Creating new environment '$EnvName'..."
    conda create -y -n $EnvName python=$PythonVersion
} else {
    Write-Host "Environment '$EnvName' already exists."
}

# --- Activate Environment ---
Write-Host "Activate environment'$EnvName'..."
conda activate $EnvName

# --- Test Environment ---
Write-Host "Testing environment '$EnvName'..."
python --version

# --- Package Installation ---
Write-Host "Installing all Python packages via pip from requirements.txt..."
& conda run -n $EnvName pip install -r requirements.txt --cache-dir="$CACHE_DIR" --progress-bar=on

Write-Host "`nInstalling the local RMT environment package in editable mode..."
& conda run -n $EnvName pip install -e . --cache-dir="$CACHE_DIR" --progress-bar=on

# Clean up Pip Cache
Remove-Item -Recurse -Force $CACHE_DIR

# --- Register Kernel for Jupyter/VS Code ---
Write-Host "Registering kernel for Jupyter/VS Code..."
& conda run -n $EnvName python -m ipykernel install --user --name $EnvName --display-name "Python ($EnvName)"

# --- VS Code Interpreter Note ---
Write-Host "`n--- VS Code Configuration ---"
Write-Host "The environment '$EnvName' is ready."
Write-Host "Please open VS Code and select the interpreter manually if not detected:"
Write-Host "1. Press Ctrl+Shift+P"
Write-Host "2. Type 'Python: Select Interpreter'"
Write-Host "3. Choose the Conda environment named '$EnvName'."

# --- VS Code Extensions ---
$install_vsc = Read-Host -Prompt "Do you want to install recommended VS Code extensions? (y/n)"
if ($install_vsc.ToLower() -in @('y', 'yes', 'j', 'ja')) {
    Write-Host "Installing VS Code extensions..."
    if (Get-Command code -ErrorAction SilentlyContinue) {
        $extensions = @(
            "ms-python.python",
            "ms-toolsai.jupyter",
            "ms-toolsai.jupyter-keymap",
            "ms-toolsai.jupyter-renderers",
            "ms-vscode.cpptools-extension-pack",
            "GitHub.vscode-pull-request-github",
            "eamodio.gitlens",
            "repreng.csv"
        )

        foreach ($ext in $extensions) {
            if (-not (code --list-extensions | Select-String $ext)) {
                Write-Host "Installing $ext..."
                code --install-extension $ext
            } else {
                Write-Host "$ext is already installed."
            }
        }
    } else {
        Write-Host "VS Code 'code' command not found. Skipping extension installation."
    }
} else {
    Write-Host "Skipping installation of VS Code extensions."
}

Write-Host "`nSetup complete! Please restart VS Code."
