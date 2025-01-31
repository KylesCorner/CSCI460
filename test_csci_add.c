#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYS_csci_add 336

int main() {
    int num1 = 10, num2 = 20;
    int result;

    printf("csci_add: %d and %d...\n", num1, num2);
    long status = syscall(SYS_csci_add, num1, num2, &result);

    if (status == 0)
        printf("Result = %d\n", result);
    else
        printf("System call failed! Error code: %ld\n", status);

    return 0;
}

