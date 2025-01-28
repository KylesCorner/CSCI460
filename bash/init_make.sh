#!/bin/bash
#
# init_make.sh
# Author: Kyle Krstulich
# Jan 27, 2025
#
# The purpose of this script is expedite the kernel compilation
# by aggressively assigning all the available system resources 
# for compilation. Needs sudo permission to function.
#

# Define the path to your log folder. These will have to be changed
# depending on your system.
LOG_DIR="/home/kyle/scripts/bash/logs/"
KERNEL_DIR="/home/kernel/linux-6.8/"

# Create the log directory if it doesn't exist
mkdir -p "$LOG_DIR"

# Define the build steps
COMMANDS=("clean" "c_compiler" "module_install" "final_install")

# Navigate to the kernel directory
cd ${KERNEL_DIR}

# Run each make command sequentially using case statement
for NAME in "${COMMANDS[@]}"; do
    OUTPUT_LOG="${LOG_DIR}${NAME}_output.log"
    ERROR_LOG="${LOG_DIR}${NAME}_error.log"
    
    # Use case statement to run specific commands
    case "$NAME" in
        "clean")
		# Removes unnecessary/unutilized object references from MakeFile
		echo "Cleaning up old objects..."
		if make -j$(nproc) clean >"$OUTPUT_LOG" 2> "$ERROR_LOG"; then
			echo "$Name Completed. Continuing..."
		else
			echo "Error detected in $ERROR_LOG. Stopping further builds."
			exit 1
		fi
            ;;

        "c_compiler")
		# Compiles C files using the ccache and gcc compilers
		echo "Compiling, this will take a while..."
		if make -j$(nproc) CC="ccache gcc" >"$OUTPUT_LOG" 2>"$ERROR_LOG"; then
			echo "$Name Completed. Continuing..."
		else
			echo "Error detected in $ERROR_LOG. Stopping further builds."
			exit 1
		fi
            ;;

        "module_install")
		# Assuming all binaries compile without error, installs them to the kernels modules directory
		echo "Installing modules..."
		if make -j$(nproc) modules_install >"$OUTPUT_LOG" 2>"$ERROR_LOG"; then
			echo "$Name Completed. Continuing..."
		else
			echo "Error detected in $ERROR_LOG. Stopping further builds."
			exit 1
		fi
            ;;

        "final_install")
		# Copies compiled binaries into their respective directories
		echo "Finilizing install.."
		if make -j$(nproc) install >"$OUTPUT_LOG" 2>"$ERROR_LOG"; then
			echo "$Name Completed. Continuing..."
		else
			echo "Error detected in $ERROR_LOG. Stopping further builds."
			exit 1
		fi
            ;;
        *)

		echo "Unknown command: $NAME"
		exit 1  # Exit with error status
            ;;
    esac
    
done

# If all commands complete successfully
echo "All builds completed without errors."

