# Programming Assignment Two - File I/O & Device Driver

## Overview
This project explores file I/O operations and basic device driver implementation using a Loadable Kernel Module (LKM). It consists of two parts:

1. **User-Space Test Program** - An interactive program that allows users to read from, write to, and seek within a file.
2. **Custom Device Driver** - A kernel module that provides a custom character device for performing I/O operations.

## Part A - User-Space Test Program
The test program takes a filename as input and allows interactive file manipulation.

### Features:
- **Read**: Reads a specified number of bytes from the file.
- **Write**: Writes user-provided text to the file.
- **Seek**: Moves the file pointer based on user input.

### Usage:
```sh
./pa2test <filename>
```


### Commands:
- **`r`** - Read data from the file.
- **`w`** - Write data to the file.
- **`s`** - Seek to a specified position.
- **`Ctrl+D`** - Exit the program.

# Part B 

This project is a **character device driver** implemented as a **Loadable Kernel Module (LKM)** for Linux. It allows user-space programs to interact with a custom `/dev/pa2_char_device` file using standard file operations such as **read, write, and seek**.

## **Features**
- Registers a character device with a **configurable major number** (default: `155`).
- Implements `open()`, `read()`, `write()`, and `llseek()` operations.
- Supports user-space interaction via `/dev/pa2_char_device`.
- Logs kernel messages for debugging (`dmesg`).
- Comes with a **test program (`pa2test.c`)** for validating driver functionality.

## **Assigning a Major Number**
Open the devices.txt file:
```bash
vim /home/kernel/linux-6.8/Documentation/admin-guide/devices.txt​
```
In the block labeled non-serial major numbers find a number with no assignment. I found the number 155

## **Installation & Usage**
### **1. Compile the Driver**
```bash
make
```

### **2. Load the Module**
```bash
sudo insmod pa2_char_driver.ko
```

### **3. Create a Device Node**
```bash
sudo mknod -m 777 /dev/pa2_char_device c 155 0
```

### **4. Run the Test Program**
```bash
./pa2test /dev/pa2_char_device
```

### **5. Unload the Module**
```bash
sudo rmmod pa2_char_driver
```

### **6. Verification**
```bash
dmesg | tail
```

Manual test:
```bash
echo "Hello" > /dev/pa2_char_device
cat /dev/pa2_char_device
```




