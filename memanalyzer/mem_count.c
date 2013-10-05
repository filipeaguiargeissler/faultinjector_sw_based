#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fdin, fdout;
	char *src, *dst;
	struct stat statbuf;

	unsigned int *val;
	int i;
	int count = 0;

	/* open the input file */
	if ((fdin = open (argv[1], O_RDONLY)) < 0)
		printf("error1\n");

	/* find size of input file */
	if (fstat (fdin,&statbuf) < 0)
		printf("error 2\n");

	/* mmap the input file */
	if ((src = mmap (0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0))
			== (caddr_t) -1)
		printf("error 2\n");

	val = (unsigned int*)src;

	for (i = 0; i < statbuf.st_size/4; i++)
		if (val[i] == 0xabababab)
			count++;

	printf("count total=%d\n", count);

	return 0;
}
