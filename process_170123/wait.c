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
	int status;
	pid_t cpid=wait(&status);
	if(WIFEXITED(status))
	{
	printf("cpid=%d\n",cpid);
	printf("child exit value=%d\n",WEXITSTATUS(status));
	}else{
	printf("child crash\n");
	}
	printf("i am parent\n");
	printf("pid=%d\n",getpid());
	sleep(5);
	return 0;
	}
}
