#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "Wrong amount of arguments passed!\n");
	}
	
	int pid = fork();
	
	if (pid == 0)
	{
		if( execl(argv[1], argv[1], (char*)NULL) == -1)
		{
			err(2, "Error while trying to execute child process\n");
		}				
	}
	
	int pid2 = fork();
	if (pid2 == 0)
	{
		if( execl(argv[2], argv[2], (char*)NULL) == -1)
		{
			err(2, "Error while trying to execute child process\n");
		}
	}
	
	int status;
	int first_proc = wait(&status);
	
	if(WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		printf("%d\n", first_proc);
		exit(0);
	}
	
	int second_proc = wait(&status);
	if(second_proc == -1)
	{
		err(5, "Error while waiting for child proccess");
	}

	if(WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		printf("%d\n", second_proc);
		exit(0);		
	}
	
	printf("-1\n");
	exit(0);
}
