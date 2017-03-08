#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
int main()
{
	if(fork())
	{
	exit(0);
	}
	printf("current pid=%d\n",getpid());
	setsid();
	chdir("/");
	umask(0);
	int maxfd,i=0;
	for(;i<maxfd;i++)
	close(i);
	while(1);
	return 0;
}
