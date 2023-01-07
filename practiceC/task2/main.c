#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <unistd.h>
	
int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		errx(1 ,"Not enough arguments for cp to work");
	}
	
	int src = open(argv[1], O_RDONLY);
	
	if (src == -1)
	{
		err(2 ,"Error while trying to open file src");
	}
	
	for(int i = 2; i < argc; i++)
	{
		int dst = open(argv[i], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		
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
		
		close(dst);
		
		if (r_status == -1)
		{
			close(src);
			errx(2 ,"Error while trying to read from src file");	
		} 
		
		if ( w_status == -1)
		{
			close(src);
			errx(3 ,"Error while trying write into dst file");	
		}
		
		lseek(src, 0, SEEK_SET);
	}
	
	close(src);
	
	exit(0);
}
