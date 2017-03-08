#include"func.h"

void newsig(int signum,siginfo_t *p,void *oldact)
{
	printf("before sleep the signum=%d\n",signum);
	sleep(2);
	printf("after sleep the signum=%d\n",signum);
}
int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(struct sigaction));
	act.sa_sigaction=newsig;
	act.sa_flags=SA_SIGINFO|SA_NODEFER;
	sigaction(SIGQUIT,&act,NULL);
	sigaction(SIGINT,&act,NULL);
	while(1);
	return 0;
}


