#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc,char **argv)
{
	if(2!=argc)
	{
		printf("error args");
		return -1;
	}
	int i,shmid;
	int *p;
	key_t k;
	pid_t pid;
	k=ftok(argv[1],1);
	printf("k=%d\n",k);
    shmid=shmget(k,1<<21,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmid");	
		return -1;
	}
	printf("shmid=%d\n",shmid);
	p=(int*)shmat(shmid,NULL,0);
	if((int*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	*p=0;           //父子进程谁先执行未知，执行前初始化0
	if(0==(pid=fork()))
	{
		printf("i am child\n");
		printf("pid=%d,ppid=%d\n",getpid(),getppid());
		int *p;
		p=(int*)shmat(shmid,NULL,0);
		if((int*)-1==p)
		{
			perror("shmat");
			return -1;
		}
		for(i=0;i<10000000;i++)
			*p+=1;
		printf("child exit *p=%d\n",*p);
		exit(0);
	}else{
		printf("i am parent\n");
		printf("pid=%d,child pid=%d\n",getpid(),pid);
		int *p;
		p=(int*)shmat(shmid,NULL,0);
		if((int*)-1==p)
		{
			perror("shmat");
			return -1;
		}
		for(i=0;i<10000000;i++)
			*p+=1;
		printf("parent exit *p=%d\n",*p);
		wait(NULL);
		return 0;
		}
}
