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
- `sudo make -j2 install`.

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


## Grub Menu(Fixed)
`grub-menu.sh` is Ahn's script from the [programming
assignment](https://canvas.umt.edu/courses/18301/assignments/228633).
I fixed the syntax errors. The script doesn't actually affect grub in any way. It
just views the configuration file with a pretty menu, with no way to change
anything. Requires sudo permission.
### Installation
Paste this into your terminal.
```bash
wget https://github.com/KylesCorner/CSCI460/blob/master/tools/grub-menu.sh
sudo chmod +x grub-menu.sh
```

### Useful Example
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

## Vim
From [vims website](https://www.vim.org/)
> Vim is a highly configurable text editor built to make creating and changing
> any kind of text very efficient. It is included as "vi" with most UNIX systems
> and with Apple OS X.
Here is my configuration for vim on my virtual machine. Vim has a steep learning
curve, but in my opinion it is the fastest way to write code. Here is a list of

My configuration has some extra keybinds and side effects.
- `jk` pressed in quick succession puts you into command mode. Equivalent to `esc`.
- `<Space>s` turns on spell check.
- `<Space>l` toggles tab indicator.
- `o and O` keeps you in command mode instead of putting you into insert mode
  after creating a new line.

## Installion
Paste this into your terminal.
```bash
sudo apt install vim
cd ~
wget https://github.com/KylesCorner/CSCI460/blob/master/tools/.vimrc
```

## Useful Example
```bash
vim textfile.txt
```
Here is a brief [lesson on vim](https://datascientest.com/en/vim-the-comprehensive-guide-to-this-text-editor).
