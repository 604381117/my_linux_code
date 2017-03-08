#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
int main(int argc,char **argv)
{
	if(2!=argc)
	{
		printf("error args");
		return -1;
	}
	int shmid;
	char *p;
	key_t k;
	k=ftok(argv[1],1);
	printf("k=%d\n",k);
	shmid=shmget(k,1<<20,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	printf("shmid=%d\n",shmid);
	p=(char*)shmat(shmid,NULL,0);
	if((char*)-1==p)
	{
		perror("shmat");
		return -1;
	}
		strcpy(p,"How are you");	
	while(1);
	return 0;
}
