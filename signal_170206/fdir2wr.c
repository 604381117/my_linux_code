#include"func.h"
#define N 100

int shmid,pida;
char *p;

void handle(int num)
{
	kill(pida,SIGINT);
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
	int fdw,fdr;
	char buf[N]={0};
	int ret;
	fd_set rdset;
	shmid=shmget(1235,4096,IPC_CREAT|0666);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	p=(char*)shmat(shmid,NULL,0);
	if((char*)-1==p)
	{
		perror("shamt");
		return -1;
	}
	fdw=open("fifo1",O_WRONLY);//open fifo1 write pot
	if(-1==fdw)
	{
		perror("open1w");
		return -1;
	}
	fdr=open("fifo2",O_RDONLY);//open fifo2 read pot
	if(-1==fdr)
	{
		perror("open2r");
		return -1;
	}
	char s1[10]={0},s2[10]={0};
	sprintf(s1,"%d\n",getpid());
	write(fdw,s1,strlen(s1)-1);
	read(fdr,s2,strlen(s1)-1);
	pida=atoi(s2);
	printf("pipe connect success,shmid=%d,pida=%d...\n",shmid,pida);
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
