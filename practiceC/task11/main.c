#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		errx(1, "Wrong amount of arguments!\n");
	}
	
	int success = 0;
	int failed = 0;
	
	for(int i = 1; i < argc; i++)
	{
		int pid = fork();
		int status;
		
		if(pid == 0)
		{
			if (execl(argv[i], argv[i], (char *) NULL) == -1)
			{
				err(2, "Child assigned process failed to execute!\n");
			}
		}
		
		wait(&status);
		if(WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			success++;
		}
		else
		{
			failed++;
		}
	}
	
	printf("Succeful: %d\nFailed: %d\n", success, failed);
	
	exit(0);
}
