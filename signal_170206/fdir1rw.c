#include"func.h"
#define N 100

int shmid,pidb;
char *p;

void handle(int num)
{
	kill(pidb,SIGINT);
	shmdt(p);
	int ret=shmctl(shmid,IPC_RMID,NULL);
	if(-1==ret)
	{
		perror("shmctl");
		return (void)-1;
	}
	printf("delete shared memory success...\n");
	exit(0);
}

int main(int argc,char **argv)
{   
	signal(SIGINT,handle);
	int fdr,fdw;
	char buf[N]={0};
	int ret;
	fd_set rdset;
	shmid=shmget(1234,4096,IPC_CREAT|0666);
	if(shmid==-1)
	{
		perror("shmget");
		return -1;
	}
	p=(char*)shmat(shmid,NULL,0);
	if((char*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	fdr=open("fifo1",O_RDONLY);//open fifo1 read pot
	if(-1==fdr)
	{
		perror("open1r");
		return -1;
	}
	fdw=open("fifo2",O_WRONLY);//open fifo2 write pot
	if(-1==fdw)
	{
		perror("open2w");
		return -1;
	}
	char s1[10]={0},s2[10]={0};
	sprintf(s1,"%d\n",getpid());
	write(fdw,s1,strlen(s1)-1);
	read(fdr,s2,strlen(s1)-1);
	pidb=atoi(s2);
	printf("pipe connect success,shmid=%d,pidb=%d...\n",shmid,pidb);
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(fdr,&rdset);
		ret=select(fdr+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&rdset))
			{
				memset(buf,0,sizeof(buf));
				if(read(fdr,buf,sizeof(buf)-1)>0)
				{
					strcpy(p,buf);
				}else{
					break;
				}
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				if(read(STDIN_FILENO,buf,sizeof(buf))>0)
				{
					write(fdw,buf,strlen(buf)-1);
				}else{
					break;
				}
			}
		}
	}
	close(fdr);
	return 0;
}

