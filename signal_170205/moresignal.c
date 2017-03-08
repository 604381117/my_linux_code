#include"func.h"

void sig(int num)
{
	printf("\nbefor sleep signal num=%d\n",num);	
	sleep(3);
	printf("after sleep signal num=%d\n",num);	
}

int main(void)
{
	if(SIG_ERR==signal(SIGINT,sig)) //2号
	{
		perror("signal");
		exit(-1);
	}
	signal(SIGQUIT,sig);//3号
	while(1);
	return 0;
}


