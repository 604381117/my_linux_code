#include"func.h"
int main()
{
	pid_t pid=fork();
	if(!fork())
	{
	printf("pid=%d,pgid=%d\n",getpid(),getpgid(0));
	setpgid(0,0);
	printf("pid=%d,pgid=%d\n",getpid(),getpgid(0));
	exit(1);
	}else{
	printf("i am parent\npid=%d,pgid=%d\n",getpid(),getpgid(0));
	int status;
	wait(&status);
	if(WIFEXITED(status))
	{
	printf("the return value=%d\n",WEXITSTATUS(status));
	}
	sleep(5);
	return 0;
	}
}
