#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "Wrong amount of arguments passed");
	}
	
	int pid = fork();
	int status;
	if (pid == 0)
	{
		//we are int child proccess
		if( execl(argv[1], argv[1], (char*) NULL) == -1)
		{
			err(2, "Error while trying to execute %s\n", argv[1]);
		}
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		if(WEXITSTATUS(status) == 0)
		{
			printf("%s\n", argv[1]);
		}
	}
	
	exit(0);
}
