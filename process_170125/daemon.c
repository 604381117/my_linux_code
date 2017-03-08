#include"func.h"

int main()
{
	int maxfd=3;
	if(fork())
	{
	exit(0);
	}
	setsid();
	chdir("/");//改变当前目录为根目录
	int i;
	for(i=0;i<maxfd;i++)
	close(i);
	while(1);
	return 0;
}
