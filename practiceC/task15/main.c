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

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "Wrong amount of arguments");
	}
	
	if (mkfifo("mypipe", S_IRUSR | S_IWUSR) == -1)
	{
		if (errno != EEXIST)
		{
			err(2, "Error while trying to create a named pipe");
		}
	}
	
	int fd = open("mypipe", O_WRONLY);
	if (fd == -1)
	{
		err(3, "Error while trying to write into fifo file");
	}
	
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		err(4, "Error while trying to duplicate pipe");
	}
	
	if( execl("/bin/cat", "cat", argv[1], (char*)NULL) == -1)
	{
		close(fd);
		err(5, "Error while trying to execute cat with given argument");
	}
	
	exit(0);
}
