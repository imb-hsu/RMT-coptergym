#!/bin/bash

# chmod a+x zip_current_folder.sh 
# Get the current folder name
current_folder=$(basename "$PWD")
BASEDIR="$PWD"
echo "try to zip: ${current_folder} from ${BASEDIR}"

# Get the current date in YYYY-MM-DD format
current_date=$(date +%Y-%m-%d)

# Move up one directory
cd $HOME || { echo "Failed to navigate to the parent directory."; exit 1; }

# Zip the folder into a file named with the current folder name and date
zip -r --symlinks "${current_folder}_${current_date}.zip" "$BASEDIR" || { echo "Failed to create zip file."; exit 1; }

# Confirmation message
echo "Successfully created ${current_date}_RLTraining_${current_folder}.zip in $(pwd)."