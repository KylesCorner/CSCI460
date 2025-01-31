#! /bin/bash
#
#
# This variable will need to be changed depending on your system.
# Below is the directory for the custom kernel for the UM VM.
#KERNEL_DIR="/home/kernel/home/kernel/linux-hwe-4.15.0"
KERNEL_DIR="/home/kernel/linux-6.8"

# This variable also needs to be changed. Its the direct path to your test
# program
TEST_PGM="/code/test_csci_add.c"

# zip up assignment files and throwing away the path.
sudo zip -j assignment1b.zip "$KERNEL_DIR/arch/x86/kernel/csci_add.c" "$KERNEL_DIR/arch/x86/kernel/Makefile" "$KERNEL_DIR/arch/x86/entry/syscalls/syscall_64.tbl" "$KERNEL_DIR/include/linux/syscalls.h" "$TEST_PGM" "/var/log/syslog"

# peek inside zip file
unzip -l assignment1b.zip
