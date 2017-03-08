#include"func.h"
void sig(int signum)
{
	time_t t;
	time(&t);
	struct tm *pTm=gmtime(&t);
	printf("%04d-%02d-%02d %02d:%02d:%02d\n",
	(1900+pTm->tm_year),(1+pTm->tm_mon),pTm->tm_mday,
	(8+pTm->tm_hour),pTm->tm_min,pTm->tm_sec);
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
	sleep(3);
	while(1);
	return 0;
}


