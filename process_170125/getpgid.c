#include"func.h"
int main()
{
	pid_t pid=fork();
	if(!fork())
	{
	printf("pid=%d,pgid=%d\n",getpid(),getpgid(0));
	exit(0);
	}else{
	printf("i am parent\npid=%d,pgid=%d\n",getpid(),getpgid(0));
	wait(NULL);
	return 0;
	}
}
