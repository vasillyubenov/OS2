#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1 ,"Not enough arguments for cp to work");
	}
	
	int src = open(argv[1], O_RDONLY);
	
	if (src == -1)
	{
		err(2 ,"Error while trying to open file src");
	}
	
	int dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	
	if (dst == -1)
	{
		close(src);
		err(2 ,"Error while trying to open file dst");
	}
	
	char c;
	int r_status;	
	int w_status;	
	
	while( ( r_status = read(src, &c, 1) ) > 0)
	{
		if ( (w_status = write(dst, &c, 1) ) != 1)
		{
			break;
		}
	}
	
	close(src);
	close(dst);
	
	if (r_status == -1)
	{
		errx(2 ,"Error while trying to read from src file");	
	} 
	
	if ( w_status == -1)
	{
		errx(3 ,"Error while trying write into dst file");	
	}
	
	exit(0);
}
