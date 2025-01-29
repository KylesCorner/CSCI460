# Tools

## Speedy Kernel Compiler
`init_make.sh` is a small bash script that runs the make commands necessary to
compile the linux kernel. It will utilizes all processing cores on the system in
order to do this. Requires sudo permission.

For the [programming
assignment](https://canvas.umt.edu/courses/18301/assignments/228633) use this
script instead of running the commands 
- `cd /home/kernel/linux-hwe-4.15.0`
- `sudo make -j2 CC="ccache gcc"`
- `sudo make -j2 modules_install`
-`sudo make -j2 install`.

### Installation
Paste this into your terminal.
```bash
wget https://github.com/KylesCorner/CSCI460/blob/master/tools/init_make.sh
sudo chmod +x init_make.sh
```

Near the top of the file there should be two variables that need to be remapped.
- `KERNEL_DIR` should be the path to the linux kernel folder on your machine.
- `LOG_DIR` should be the path to the directory where you want error and log
  files to be stored.

### Useful Example
`sudo ./init_make.sh`


