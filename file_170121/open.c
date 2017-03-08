#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		puts("error args");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDONLY|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("fd=%d\n",fd);
	close(fd);
	return 0;
}

