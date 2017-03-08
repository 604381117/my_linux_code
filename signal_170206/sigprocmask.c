#include"func.h"

void newsig(int signum,siginfo_t *p,void *oldact)
{
	printf("signum %d is coming\n",signum);
}

int main()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	int ret=sigprocmask(SIG_BLOCK,&set,NULL);
	if(-1==ret)
	{
		perror("sigprocmask");
		exit(-1);
	}
	sleep(5);
	sigset_t set2;
	sigemptyset(&set2);
	sigpending(&set2);
	if(sigismember(&set2,SIGINT))
	{
		printf("SIGINT PENDING\n");
	}else{
		printf("SIGINT NOT PENDING\n");
	}
	ret=sigprocmask(SIG_UNBLOCK,&set,NULL);
	if(-1==ret)
	{
		perror("sigprocmask");
		exit(-1);
	}
	while(1);
	return 0;	
}

