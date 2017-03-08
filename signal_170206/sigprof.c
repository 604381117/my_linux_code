#include"func.h"

void sig(int signum)
{
	time_t t;
	time(&t);
	printf("%s\n",ctime(&t));
}

int main()
{
	signal(SIGPROF,sig);
	kill(0,SIGPROF);
	struct itimerval t;
	memset(&t,0,sizeof(t));
	t.it_value.tv_sec=3;
	t.it_interval.tv_sec=2;
	int ret=setitimer(ITIMER_PROF,&t,NULL);
	if(-1==ret)
	{
		perror("setitimer");
		exit(-1);
	}
	while(1);
	//char buf[50]={0};
	//read(0,buf,sizeof(buf));
	return 0;
}
