#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		perror("error args");
		return -1;
	}	
	int fd;
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	int ret;
	ret=ftruncate(fd,1<<20);
	if(ret==-1)
	{
		perror("ftruncate");
		return -1;
	}
	close(fd);
	return 0;
}
