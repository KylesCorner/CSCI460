# pa_1_helper.sh
#
# This prints out the syscall made in programming assignment 1 part a
KERNEL_DIR="/home/kernel/linux-6.8/"


sudo tail /var/log/syslog | grep "Hello world!"
cat "$KERNEL_DIR"arch/x86/entry/syscalls/syscall_64.tbl | grep helloworld
cat "$KERNEL_DIR"arch/x86/kernel/helloworld.c
