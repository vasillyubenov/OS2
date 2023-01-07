#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

struct test {
    uint8_t a;
    uint16_t b;
}__attribute__((packed));

int main(void)
{
	struct test vasko = {
		.a = 5,
		.b = 4
	};
	
	printf("%ld\n", sizeof(vasko));
	

	exit(0);
}
