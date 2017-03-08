#include"func.h"

void newsig(int signum,siginfo_t *p,void *oldact)
{
	printf("befor sleep signum=%d\n",signum);	
	sleep(2);
	sigset_t set;
	sigemptyset(&set);
	sigpending(&set);
	if(sigismember(&set,SIGQUIT))
	{
		printf("SIGQUIT IS PENDING\n");
	}else{
		printf("SIGQUIT IS NOT PENDING\n");
	}
	printf("befor sleep signum=%d\n",signum);	
}

int main()
{
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=newsig;
	sigset_t set;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);
	int ret=sigaction(SIGINT,&act,NULL);
	if(-1==ret)
	{
		perror("sigaction signum2");
		exit(-1);
	}
	//ret=sigaction(SIGQUIT,&act,NULL);
	if(-1==ret)
	{
		perror("sigaction signum3");
		exit(-1);
	}
	while(1);
	return 0;
}


