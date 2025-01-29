#include <stdio.h>

// These are needed to make a syscall()
#include <sys/syscall.h>
#include <unistd.h>

#define SYS_helloworld 335

int main(){

	//envoke helloworld syscall
	//https://man7.org/linux/man-pages/man2/syscall.2.html
	long res = syscall(SYS_helloworld);

	// returning 0 means it finished executing
	if(res == 0){
		printf("System call executed successfully!\n");
	}else{

		printf("System call failed.\n");

	}

	return 0;

}
