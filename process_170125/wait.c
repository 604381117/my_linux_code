#include"func.h"
int main()
{
	if(!fork())
	{
	printf("i am child\n");
	sleep(5);
	exit(0);
	}else{
	wait(NULL);
	printf("i am parent\n");
	sleep(10);
	printf("after sleep\n");
	return 0;
	}
}
