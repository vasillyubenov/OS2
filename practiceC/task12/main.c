#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		errx(1, "Wrong amount of arguments passed!\n");
	}
	
	int fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	
	if (fd == -1)
	{
		err(2, "Error while trying to open file to write into!\n");
	}
	
	const int procs = 2;
	for (int i = 1; i <= procs; i++)\
	{	
		int pid = fork();
		
		if (pid == 0)
		{
			if( execl(argv[i], argv[i], (char*)NULL) == -1)
			{
				err(3, "Error while trying to execute first process!\n");
			}	
		}
		
		int status;
		wait(&status);
		
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			int size = strlen(argv[i]);
			if (write(fd, argv[i], size) < size)
			{
				close(fd);
				err(4, "Error occured while trying to write into file");
			}
			
			const char nl = '\n';
			
			if (write(fd, &nl, 1) < 1)
			{
				err(4, "Error occured while trying to write into file");
			}
		}
		else
		{
			printf("Proccess %s failed.\n", argv[i]);
		}	
	}
	
	exit(0);
}
