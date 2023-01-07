#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "Should only give file to paste in name\n");
	}
	
	int src = open("/etc/passwd", O_RDONLY);
	
	if(src == -1)
	{
		err(2, "Error while tryong to read from /etc/passwd\n");
	}
	
	int dst = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	
	if(dst == -1)
	{
		close(src);
		err(3, "Error while trying to open %s for writing\n", argv[1]);
	}
	
	char c;
	
	int r_status;
	int w_status;
	
	while ( (r_status = read(src, &c, 1)) > 0 )
	{
		if (c == ':')
		{
			c = '?';
		}
		if ( (w_status = write(dst, &c, 1)) != 1 )
		{
			close(src);
			close(dst);
			errx(4, "Error while trying to write into %s\n", argv[1]);;
		} 
	}
	
	close(src);
	close(dst);
	
	if (r_status == -1)
	{
		err(5, "Error while trying to read from /etc/passwd\n");
	}
	
	exit(0);
}
