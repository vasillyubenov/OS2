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
	const int size = 3;
	if (argc != size + 1)
	{
		errx(1, "Wrong amount of arguments passed");
	}
	
	for(int i = 1; i < argc; i++)
	{
		int pid = fork();
		int status;
		if (pid == 0)
		{
			//we are int child proccess
			if( execl(argv[i], argv[i], (char*) NULL) == -1)
			{
				err(2, "Error while trying to execute %s\n", argv[i]);
			}
		}
		
		wait(&status);
		
		if (WIFEXITED(status))
		{
			printf("%s exited with status %d\n", argv[i], WEXITSTATUS(status));
		}	
	}
	
	exit(0);
}
