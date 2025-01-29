# Operating Systems! 

This is the repository for my operating systems class CSCI460. My toolchain is
stored in the bash folder. Please read the comments before executing.

## Useful Links
Kernel documentation for adding a new [system call](https://www.kernel.org/doc/html/latest/process/adding-syscalls.html)

## Useful Commands
`sudo apt update && sudo apt upgrade -y && sudo apt install build-essential ccache gcc make libssl-dev -y`
> Updates application repositories and installs necessary packages

## Tool Chain
For `init_make.sh` you need to edit the `KERNEL_DIR` and `LOGS_DIR` to fit your
system. Run this script instead of the 'make' commands listed in the
[programming assignment](https://canvas.umt.edu/courses/18301/assignments/228633).
