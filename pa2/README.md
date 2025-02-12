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

