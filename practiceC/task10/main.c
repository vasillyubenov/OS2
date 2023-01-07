#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		errx(1, "Wrong amount of arguments!\n");
	}
	
	int pid = fork();
	int status;
	
	if(pid == 0)
	{
		if (execl(argv[1], argv[1], (char *) NULL) == -1)
		{
			err(2, "Child assigned process failed to execute!\n");
		}
	}
	
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		printf("%s\n", argv[1]);
		if( execl(argv[2], argv[2], (char*) NULL) == -1)
		{
			err(3, "Father process failed to execute");
		}
		
		
	}
	else
	{
		exit(42);
	}
	
	exit(0);
}
