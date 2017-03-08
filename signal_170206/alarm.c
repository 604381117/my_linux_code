#include"func.h"

void sig(num)
{
	printf("num=%d\n",num);
}

int main()
{
	signal(SIGALRM,sig);
	alarm(3);//设定3秒以后，定时器向当前进程发送alarm信号
	pause();
	while(1);
	return 0;
}
