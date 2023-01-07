#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "Wrong amount of arguments");
	}

	int fd = open("../mypipe", O_RDONLY);
	if (fd == -1)
	{
		err(3, "Error while trying to write into fifo file");
	}
	
	int pid = fork();
	if (pid == -1)
	{
		err(7, "Error while trying to fork the proccess");
	}
	
	if( pid == 0)
	{
		if (dup2(fd, 0) == -1)
		{
			close(fd);
			err(4, "Error while trying to duplicate pipe");
		}
		
		if( execl(argv[1], argv[1], (char*)NULL) == -1)
		{
			close(fd);
			err(5, "Error while trying to execute cat with given argument");
		}	
	}	
	
	if (wait(NULL) == -1)
	{
		err(8, "Error while waiting for cghild proc to finish");
	}
	
	exit(0);
}
