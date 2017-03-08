#include"func.h"

void sig(int num)
{
	printf("signal num=%d\n",num);	
}

int main(void)
{
	if(SIG_ERR==signal(SIGINT,sig))
	{
		perror("signal");
		exit(-1);
	}
	while(1);
	return 0;
}
