#include"func.h"

int main(int argc,char **argv)
{
	if(argc!=2)
	{
	printf("error args");
	return -1;
	}	
	int fd,fd1;
	fd=open(argv[1],O_RDWR)
	if(-1==fd)
	{
	perror("open");
	return -1;
	}
	char buf[20]={0};
	fd1=fd;
	fd1=dup(fd);
	close(fd);
	printf("fd1=%d\n",fd1);
	int ret=read(fd1,buf,sizeof(buf));
	printf("ret=%d,errono=%d\n",ret,errno);
	puts(buf);
	return 0;
}
