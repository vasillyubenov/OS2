#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc != 2)
		errx(1, "Wrong number of arguments passed!");

	int a[2];
	if(pipe(a) == -1)
	{
		err(5, "Error while trying to pipe");
	}

	int pid = fork();
	
	if (pid == 0)
	{
		close(a[0]);
		dup2(a[1], 1);
		if(execl("/bin/cat", "/bin/cat", argv[1], (char*)NULL))
		{
			err(2, "Error while trying to exec cat");
		}
		
	}
	close(a[1]);
	
	dup2(a[0], 0);
	if(execl("/bin/sort", "/bin/sort", (char*)NULL))
	{
		err(2, "Error while trying to exec sort");
	}
	
	exit(0);
}
