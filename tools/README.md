# Tools
This is where I store all my tools for CSCI460. You are free to use them just
scroll down and find the installation and usage examples. My tools include:


- Speedy Kernel Compiler: uses all processing cores for kernel compilation.
- Grub Menu(fixed): Ahn's script with fixed syntax errors.
- PA1A Zipper: script that zips files for submission.
- PA2A Zipper: ^
- VIM config: my text editor of choice.

Before you install any tools, install the dependencies.
```bash
sudo apt update && sudo apt install wget -y
```

## Speedy Kernel Compiler
`init_make.sh` is a small bash script that runs the make commands necessary to
compile the linux kernel. It will utilizes all processing cores on the system in
order to do this. Requires sudo permission.

For the [programming
assignment](https://canvas.umt.edu/courses/18301/assignments/228633) use this
script instead of running these commands 
- `cd /home/kernel/linux-hwe-4.15.0`
- `sudo make -j2 CC="ccache gcc"`
- `sudo make -j2 modules_install`
- `sudo make -j2 install`

### Installation
Paste this into your terminal.
```bash
wget https://raw.githubusercontent.com/KylesCorner/CSCI460/refs/heads/master/tools/init_make.sh
sudo chmod +x init_make.sh
```

Near the top of the file there should be two variables that need to be remapped.
- `KERNEL_DIR` should be the path to the linux kernel folder on your machine.
- `LOG_DIR` should be the path to the directory where you want error and log
  files to be stored.

### Example
```bash
sudo ./init_make.sh
```


## Grub Menu(Fixed)
`grub-menu.sh` is Ahn's script from the [programming
assignment](https://canvas.umt.edu/courses/18301/assignments/228633).
I fixed the syntax errors. The script doesn't actually affect grub in anyway. It
just views the configuration file with a pretty menu with no way to change
anything. Requires sudo permission.
### Installation
Paste this into your terminal.
```bash
wget https://raw.githubusercontent.com/KylesCorner/CSCI460/refs/heads/master/tools/grub-menu.sh
sudo chmod +x grub-menu.sh
```

### Example
```bash
sudo ./grub-menu.sh
```
On the left side of this menu you will see numbers like this 1<0 or 1<1. These
are the menu id's associated with that kernel. If you want to boot into another
kernel:
```bash
sudo grub-reboot 1<YOUR_NUMBER
sudo reboot now
```
`grub-reboot` does not reboot your computer. It assigns a kernel to boot into
next restart.

## PA1A Zipper

Used to gather and zip up submission files for the [programming
assignment](https://canvas.umt.edu/courses/18301/assignments/228633).

### Installation
```bash
wget https://raw.githubusercontent.com/KylesCorner/CSCI460/refs/heads/master/tools/pa_1_helper.sh
chmod +x pa_1_helper.sh
```
These variables need to be changed:
- `KERNEL_DIR` is the working directory of your custom kernel in
  `/home/kernel/`.

- `TEST_PGM_DIR` is the direct path to your testing program.

### Example
```bash
./pa_1_helper.sh
```
This will create `assignment.zip` in the same directory as the script, and peek
inside of the zip file.

## PA2A Zipper
Used to gather and zip up submission files for the [programming
assignment](https://canvas.umt.edu/courses/18301/assignments/228634).

### Installation
```bash
wget https://raw.githubusercontent.com/KylesCorner/CSCI460/refs/heads/master/tools/pa_1b_helper.sh
chmod +x pa_1b_helper.sh
```
These variables need to be changed:
- `KERNEL_DIR` is the working directory of your custom kernel in
  `/home/kernel/`.

- `TEST_PGM` is the direct path to your testing program.

### Example
```bash
./pa_1b_helper.sh
```
This will create `assignment1b.zip` in the same directory as the script, and peek
inside of the zip file.

## Vim
From [vims website](https://www.vim.org/)
> Vim is a highly configurable text editor built to make creating and changing
> any kind of text very efficient. It is included as "vi" with most UNIX systems
> and with Apple OS X.

Here is my configuration for vim, or `.vimrc`, on my virtual machine. Vim has a steep learning
curve, but in my opinion, **it's the fastest way to write code.** 

My configuration has some extra keybinds and side effects.
- `jk` pressed in quick succession puts you into command mode. Equivalent to `esc`.
- `<Space>s` turns on spell check.
- `<Space>l` toggles tab indicator.
- `o and O` keeps you in command mode instead of putting you into insert mode
  after creating a new line.

### Installation
Paste this into your terminal.
```bash
sudo apt update && sudo apt install vim wget -y
cd ~
wget https://raw.githubusercontent.com/KylesCorner/CSCI460/refs/heads/master/tools/.vimrc
```

### Example
```bash
vim textfile.txt
```
Vim has a built in tutorial.
```bash
vimtutor
```
Here is a list of
[default keybinds and commands](https://vim.rtorr.com/).

