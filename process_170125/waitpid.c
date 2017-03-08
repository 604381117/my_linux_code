#include"func.h"
int main()
{
	if(!fork())
	{
	printf("i am child\n");
	exit(0);
	}else{
	int status;
	pid_t cpid;
	cpid=wait(&status);
	if(WIFEXITED(status))
	{
	printf("cpid=%d\n",cpid);
	printf("childe exit value=%d\n",WEXITSTATUS(status));
	}else{
	printf("child crash\n");
	}
	printf("i am parent\n");
	return 0;
	}
}
