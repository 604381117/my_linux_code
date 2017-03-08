#include"func.h"
#define N 100

int main(void)
{ 
	char buf[N]={0};
	int shmid=shmget(1235,4096,IPC_CREAT|0666);
	if(shmid==-1)
	{
		perror("shmget");
		return -1;
	}
	char *p=shmat(shmid,NULL,0);
	while(1)
	{
		if(!strcmp(buf,p))
		{	
			continue;
		}else{
			memset(buf,0,sizeof(buf));
			strcpy(buf,p);
			printf("%90s :from A\n",buf);
		}
	}
	if(shmctl(shmid,IPC_RMID,0)==-1);
	{
		perror("shmget");
		return -1;
	}
	return 0;
}


