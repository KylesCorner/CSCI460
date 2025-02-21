// #include <cerrno>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 1024
#define MAJOR_NUMBER 155
#define DEVICE_NAME "pa2_char_driver"

static char *device_buffer;
static int major_number;
static int open_count = 0;
static int close_count = 0;
/* Define device_buffer and other global data structures you will need here */
// loff_t is a long long type.
// size_t is a 64bit unsigned integer. It is the return type of sizeof()
ssize_t pa2_char_driver_read(struct file *pfile, char __user *buffer,
                             size_t length, loff_t *offset) {

  /* *buffer is the userspace buffer to where you are writing the data you want
  to be read from the device file*/
  /* length is the length of the userspace buffer*/
  /* offset will be set to current position of the opened file after read*/
  /* copy_to_user function: source is device_buffer and destination is the
  userspace buffer *buffer */

  size_t bytes_to_read = BUFFER_SIZE - *offset;

  if (bytes_to_read > length) {
    bytes_to_read = length;
  }
  if (bytes_to_read <= 0) {
    return 0; // EOF
  }

  if (copy_to_user(buffer, device_buffer + *offset, bytes_to_read)) {
    return -EFAULT; // Error in copying data
  }

  *offset += bytes_to_read;
  printk(KERN_INFO "CSCI460: Read %zu bytes from the device\n", bytes_to_read);
  return bytes_to_read;
}
ssize_t pa2_char_driver_write(struct file *pfile, const char __user *buffer,
                              size_t length, loff_t *offset) {
  /* *buffer is the userspace buffer where you are writing the data you want to
  be written in the device file*/
  /* length is the length of the userspace buffer*/
  /* current position of the opened file*/
  /* copy_from_user function: destination is device_buffer and source is the
  userspace buffer *buffer */
  size_t bytes_to_write = BUFFER_SIZE - *offset;
  if (bytes_to_write > length) {
    bytes_to_write = length;
  }
  if (bytes_to_write <= 0) {
    return -ENOSPC; // No space left on device
  }

  if (copy_from_user(device_buffer + *offset, buffer, bytes_to_write)) {
    return -EFAULT; // Error in copying data
  }

  *offset += bytes_to_write;
  printk(KERN_INFO "CSCI460: Wrote %zu bytes to the device\n", bytes_to_write);
  return bytes_to_write;
}
int pa2_char_driver_open(struct inode *pinode, struct file *pfile) {
  /* print to the log file that the device is opened and also print the number
  of times this device has been opened until now*/
  open_count++;
  printk(KERN_INFO "CSCI460: Device opened %d times\n", open_count);
  return 0;
}
int pa2_char_driver_close(struct inode *pinode, struct file *pfile) {
  /* print to the log file that the device is closed and also print the number
  of times this device has been closed until now*/
  close_count++;
  printk(KERN_INFO "CSCI460: Device closed %d times\n", close_count);
  return 0;
}
loff_t pa2_char_driver_seek(struct file *pfile, loff_t offset, int whence) {
  /* Update open file position according to the values of offset and whence */
  loff_t new_position;

  switch (whence) {
  case SEEK_SET:
    new_position = offset;
    break;
  case SEEK_CUR:
    new_position = pfile->f_pos + offset;
    break;
  case SEEK_END:
    new_position = BUFFER_SIZE + offset;
    break;
  default:
    return -EINVAL; // Invalid argument
  }

  if (new_position < 0 || new_position > BUFFER_SIZE) {
    return -EINVAL; // Out of bounds
  }

  pfile->f_pos = new_position;
  return new_position;
}
struct file_operations pa2_char_driver_file_operations = {
    .owner = THIS_MODULE,
    .open = pa2_char_driver_open,
    .release = pa2_char_driver_close,
    .read = pa2_char_driver_read,
    .write = pa2_char_driver_write,
    .llseek = pa2_char_driver_seek,
    /* add the function pointers to point to the corresponding file operations.
    look at the file fs.h in the linux souce code*/
};
static int __init pa2_char_driver_init(void) {
  /* print to the log file that the init function is called.*/
  /* register the device */
  printk(KERN_INFO "CSCI460: Initializing the character device\n");
  device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
  if (!device_buffer) {
    return -ENOMEM; // Memory allocation failed
  }

  major_number = register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &pa2_char_driver_file_operations);

  if (major_number < 0) {
    printk(KERN_ALERT "CSCI460: Failed to register character device\n");
    kfree(device_buffer);
    return major_number;
  }
  printk(KERN_INFO "CSCI460: pa2_char_driver: registered with major number %d\n", MAJOR_NUMBER);
  return 0;
}
static void __exit pa2_char_driver_exit(void) {
  /* print to the log file that the exit function is called.*/
  /* unregister the device using the register_chrdev() function. */
  unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
  kfree(device_buffer);
  printk(KERN_INFO "CSCI460: Exiting the character device\n");
}
/* add module_init and module_exit to point to the corresponding init and exit
function*/
module_init(pa2_char_driver_init);
module_exit(pa2_char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kyle Krstulich");
MODULE_DESCRIPTION("A simple character device driver");
