### Tools

## Speedy Compiler
`init_make.sh` is a small bash script that runs the make commands necessary to
compile the linux kernel. It will utilizes all processing cores on the system in
order to do this.\

In order for you to use this script you will need to edit the `KERNEL_DIR` and
`LOGS_DIR` variables to fit your system. For the [programming
assignment](https://canvas.umt.edu/courses/18301/assignments/228633) use this
script instead of running the commands `cd /home/kernel/linux-hwe-4.15.0`, `sudo
make -j2 CC="ccache gcc"`, `sudo make -j2 modules_install` and `sudo make -j2
install`. \

# Installation

`wget https://github.com/KylesCorner/CSCI460/blob/master/tools/init_make.sh`
`sudo chmod +x init_make.sh`

