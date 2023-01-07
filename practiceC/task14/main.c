#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int cmp(const void*, const void*);

int cmp(const void * a, const void * b)
{
	if ( (int * const *)a > (int * const *)b)
	{
		return 1;
	}
	else if ((int * const *)a < (int * const *)b)
	{
		return -1;
	}
	
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "Wrong amount of arguments\n");
	}
	int fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		err(2, "Error while trying to read from file\n");
	}

	//getting the size of the file
	struct stat file_stat;	
	if( stat(argv[1], &file_stat) == -1 )
	{
		close(fd);
		err(3, "Error while trying to check stats for file\n");
	}
	
	int size = file_stat.st_size;

	printf("%d\n", size);
	
	int16_t * arr = malloc(size);
	
	int read_s;
	int i = 0;
	
	while( ( read_s = read(fd, arr+i, sizeof(int16_t))) != sizeof(int16_t))
	{
		i++;
	}
	
	close(fd);
	
	if(read_s == -1)
	{
		free(arr);
		err(4, "Error while trying to read from the file");
	}
	
	qsort(arr, size, sizeof(int16_t *), cmp);
	
	for(i = 0; i < size; i++)
	{
		printf("%d\n", arr[i]);
	}
		
	free(arr);
	
	exit(0);
}
