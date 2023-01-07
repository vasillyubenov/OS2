#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		errx(1 ,"Not enough arguments for cp to work");
	}
	
	char c;
	
	for (int i = 1; i < argc; i++)
	{
		int fd = open(argv[i], O_RDONLY);
		
		if (fd == -1)
		{
			errx(2, "Error occured while trying to read from %s", argv[i]);
		}
		
		int r_status;
		
		while(( r_status = read(fd, &c, 1) ) > 0)
		{
			if (write(1, &c, 1) != 1)
			{	
				close(fd);
				errx(4, "Error occured while trying to write to standard output");
			}
		}
		
		close(fd);
		
		if (r_status == -1)
		{
			errx(3, "Some error occured while trying to read from %s", argv[i]);
		}
	}
	exit(0);
}
