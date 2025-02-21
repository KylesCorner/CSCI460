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
In the block labeled non-serial major numbers find a number with no assignment.
I found the number 155.

## **Installation & Usage**
### **1. Compile the Driver**
```bash
make
```

### **2. Load the Module**
```bash
sudo insmod pa2_char_driver.ko
```


### **3. Run the Test Program**
```bash
./pa2test /dev/pa2_char_device
```

### **4. Unload the Module**
```bash
sudo rmmod pa2_char_driver
```

### **5. Verification**
```bash
dmesg | tail
```
You should get an output simlar to this:
```bash
[16126.006893] Exiting the character device
[16143.402680] CSCI460: Initializing the character device
[17201.769553] CSCI460: Exiting the character device
[17213.556139] CSCI460: Initializing the character device
[17213.556149] CSCI460: pa2_char_driver: registered with major number 155
[17246.253079] CSCI460: Device opened 1 times
[17246.253100] CSCI460: Read 1024 bytes from the device
[17246.253129] CSCI460: Device closed 1 times
[17265.443724] CSCI460: Device opened 2 times
[17383.201281] CSCI460: Wrote 10 bytes to the device
[17388.478910] CSCI460: Read 100 bytes from the device
[17404.080258] CSCI460: Read 100 bytes from the device
[17478.528239] CSCI460: Device closed 2 times
[18856.981366] CSCI460: Exiting the character device
[20082.826637] CSCI460: Initializing the character device
[20082.826669] CSCI460: pa2_char_driver: registered with major number 155
[20172.148005] CSCI460: Exiting the character device
[20192.116233] CSCI460: Initializing the character device
[20192.116246] CSCI460: pa2_char_driver: registered with major number 155
[20199.312957] CSCI460: Device opened 1 times
[20204.609092] CSCI460: Wrote 7 bytes to the device
[20210.577820] CSCI460: Read 100 bytes from the device
[20214.888042] CSCI460: Device closed 1 times
[20226.638004] CSCI460: Exiting the character device
```

Manual test:
```bash
echo "Hello" > /dev/pa2_char_device
cat /dev/pa2_char_device
```




