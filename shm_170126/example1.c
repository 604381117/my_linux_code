#include"func.h"
int main(int argc,char **argv)
{
	int shmid = shmget(IPC_PRIVATE,1024,PERM);
	if(-1==shmid)
	{
		fprintf(stderr,"Create Share Memory Error:%s\n\a",strerror(errno));
		exit(-1);
	}
	if(!fork())
	{
		sleep(5);
		char *c_addr=(char*)shmat(shmid,NULL,0);
		printf("Client pid=%d,shmid=%d,Read buffer:%s\n",getpid(),shmid,c_addr);
		exit(0);
	}else{
		char *p_addr=(char*)shmat(shmid,NULL,0);
		memset(p_addr,0,1024);
		strncpy(p_addr,"share memory",1024);
		printf("parent %d  Write buffer:%s\n",getpid(),p_addr);
		sleep(2);
		wait(NULL);
		shmctl(shmid,IPC_RMID,0);
		exit(0);
	}
}
