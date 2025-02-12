#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Parse command-line input
    if (argc != 2) {
        // prints contents to file not to stdout
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        // prints descriptive error
        perror("Error opening file");
        return 1;
    }

    // interactive menu loop
    char option;
    while (printf("Option (r for read, w for write, s for seek): "), scanf(" %c", &option) != EOF) {
        if (option == 'r') {
            int bytes_to_read;
            printf("Enter the number of bytes you want to read: ");
            scanf("%d", &bytes_to_read);

            // making sure malloc has a large enough buffer to read.
            char *buffer = malloc(bytes_to_read + 1);
            if (!buffer) {
                perror("Memory allocation failed");
                continue;
            }

            // print returned data to stdout with a newline char.
            ssize_t bytes_read = read(fd, buffer, bytes_to_read);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0'; 
                printf("%s\n", buffer);
            } else {
                perror("Read failed");
            }
            // free up malloc block
            free(buffer);

          //Write to file
        } else if (option == 'w') {
            char input_buffer[1024];
            printf("Enter the string you want to write: ");
            // Read strings until a newline char is entered.
            scanf(" %[^\n]", input_buffer);

            if (write(fd, input_buffer, strlen(input_buffer)) == -1) {
                perror("Write failed");
            }

          //Seek in file
        } else if (option == 's') {
            // off_t is a data type used to represent file sizes and offsets.
            off_t offset;
            int whence;
            printf("Enter an offset value: ");
            // %ld is a format specifier that indicates long int.
            scanf("%ld", &offset);
            printf("Enter a value for whence (0 for SEEK_SET, 1 for SEEK_CUR, 2 for SEEK_END): ");
            scanf("%d", &whence);

            if (lseek(fd, offset, whence) == -1) {
                perror("Seek failed");
            }
        }
    }

    // Handle Program exit.
    close(fd);
    printf("Exiting program.\n");
    return 0;
}

