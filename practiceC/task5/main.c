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

int main(int argc, char* argv[])
{
	if (argc != 3)
	{	
		errx(1, "Should only give file to paste in name\n");
	}
	else if(strcmp(argv[1], "--min") != 0 && strcmp(argv[1], "--max") != 0 && strcmp(argv[1], "--print") != 0)
	{
		errx(2, "Not correct format of passed arguments\n");
	}
	
	int fd = open(argv[2], O_RDONLY);
	
	if(fd == -1)
	{
		err(3, "Error while trying to open binary file");
	}
	
	uint16_t num;
	int r_status;
	int number = -1;
	while( (r_status = read(fd, &num, sizeof(uint16_t))) > 0)
	{	
		if (strcmp(argv[1], "--print") == 0)
		{
			printf("%d\n", num);
		}
		else if (strcmp(argv[1], "--max") == 0)
		{
			if ( number == -1 || number < num )
			{
				number = num;
			}
		}
		else
		{
			if ( number == -1 || number > num )
			{
				number = num;
			}
		}
	}
	
	close(fd);
	
	if (r_status == -1)
	{
		err(4, "Error while reading from file!\n");
	}
	
	if (number != -1)
	{
		printf("%d\n", number);
	}
		
	exit(0);
}
