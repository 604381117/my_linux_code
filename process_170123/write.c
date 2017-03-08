#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<strings.h>
#include<string.h>
int main(int argc,char **argv)
{
	if(argc!=2) 
{
	printf("error args");
	return -1;
}

	int fd;
	fd=open(argv[1],O_RDWD);
	if(-1==fd)
	{
	perror("fopen");
	return -1;
	}
	char c[20]={0};
	int ret=0;
	while(bzero(c,sizeof(c)),read(fd,c,sizeof(c)-1)>0)
	{	
	write(1,c,strlen(c));
	}
	close(fd);
	return 0;
}
