#include<stdio.h>

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("error args");
		return -1;
	}
	int fd;
	fd =fopen(argv[1],O_WR0NLY);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("\n");
	close(1);
	int fd_standout;
	fd_stdout=dup(fd);
	printf("fd_stdout=%d\n",fd_stdout);//此句看不到，实际在文件里边
	return 0;
}
