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
		errx(1, "Wrong amount of arguments\n");
	}

	int pid = fork();
	
	if (pid == 0)
	{
		int fd1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		
		if (fd1 == -1)
		{
			err(3, "Error while rtrying to open file");
		}
	
		const char * text = "foobar\0";
		int size = strlen(text);
	
		if ( write(fd1, text, size) < size)
		{
			close(fd1);
			errx(3, "Something went wrong while trying to write into %s\n", argv[1]);
		}
		
		close(fd1);
	}
	else
	{
		int status;
		wait(&status);
		int fd2 = open(argv[1], O_RDONLY);
	
		if (fd2 == -1)
		{
			close(fd2);
			err(4, "Error while trying to open the file for reading\n");
		}
		
		lseek(fd2, 0, SEEK_SET);
		char c[2];
		c[1] = ' '; 
		int r_status;
		while ( (r_status = read(fd2, &c, 1)) > 0 )
		{
			if (write(1, &c, 2) == -1 )
			{
				close(fd2);
				err(6, "Error while trying to write into standard output!\n");
			}

		}
		
		close(fd2);
		
		if(r_status == -1)
		{
			err(5, "Error while trying to read from file\n");
		}
		else
		{
			printf("\n");
		}
		
	}
	
	
	exit(0);
}
