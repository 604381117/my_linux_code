#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{
	if(!fork())
	{
	printf("i am child\n");
	printf("pid=%d,ppid=%d\n",getpid(),getppid());
	exit(0);
	}else{
	printf("i am parent\n");
	printf("pid=%d\n",getpid());
	while(1);
	}
	return 0;
}
