#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h> 
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char **argv)
{
	if(argc!=2)
	{
		perror("error args");
		return -1;
	}	
	int fd;
	int ret;
	char *p;
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	p=(char*)mmap(NULL,10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p==(char*)-1)
	{
		perror("mmap");
		return -1;
	}
	p[0]='Y';
	printf("p[0]=%c\n",p[0]);
	ret=munmap(p,10);
	if(-1==ret)
	{
		perror("munmap");
		return -1;
	}
	close(fd);
	return 0;
}
