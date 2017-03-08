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
	while(1);
	}else{
	printf("i am parent\n");
	exit(0);
	}
	return 0;
}
