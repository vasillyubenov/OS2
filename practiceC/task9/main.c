#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "Wrong amount of argments!\n");
	}
	
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	if (fd == -1)
	{
		err(2, "Error while trying to open file for reading!\n");
	}

	int pid = fork();	
	
	if (pid == 0)
	{
		const char * word = "foo";
		int size = 3;
		
		if (write(fd, word, size) < size)
		{
			close(fd);
			err(3, "Error while trying to write from child proccess\n");
		}
	}
	else
	{
		int status;
		wait(&status);
		if(WIFEXITED(status))
		{
			const char * word = "bar\n";
			int size = 4;
		
			if (write(fd, word, size) < size)
			{
				close(fd);
				err(4, "Error while trying to write from father proccess\n");
			}
		}
		
		close(fd);	
	}

	exit(0);
}
