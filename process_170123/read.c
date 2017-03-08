#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(int argc,char **argv)
{
	if(argc!=2) 
{
	printf("error args");
	return -1;
}

	int fd;
	fd=open(argv[1],O_RDWR|O_APPEND);
	if(-1==fd)
	{
	perror("fopen");
	return -1;
	}
	write(fd,"hello",5);
	lseek(fd,-5,SEEK_CUR);
	write(fd,"world",5);
	close(fd);
	return 0;
}
