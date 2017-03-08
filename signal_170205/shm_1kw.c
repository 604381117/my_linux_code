#include "fun.h"
#define N 10000000
int main()
{
	int shmid;
	shmid=shmget(1234,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	if(!fork())
	{
		int *p;
		p=(int*)shmat(shmid,NULL,0);
		if((int*)-1==p)
		{
			perror("shmat");
			return -1;
		}
		int i;
		for(i=0;i<N;i++)
		{
			*p=*p+1;
		}
		return 0;
	}else{
		int *p;
		p=(int*)shmat(shmid,NULL,0);
		if((int*)-1==p)
		{
			perror("shmat");
			return -1;
		}
		int i;
		for(i=0;i<N;i++)
		{
			*p=*p+1;
		}
		wait(NULL);
		printf("the value is %d\n",*p);
		return 0;
	}	
	return 0;
}
