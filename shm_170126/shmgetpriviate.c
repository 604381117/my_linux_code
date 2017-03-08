#include"func.h"

int main(int argc,char **argv)
{
	if(2!=argc)
	{
	printf("error args");
	return -1;
	}
	key_t k;
	k=ftok(argv[1],1);
	printf("k=%d\n",k);
	int shmid;
	shmid=shmget(IPC_PRIVATE,1<<20,IPC_CREAT|0600);
	if(-1==shmid)
	{
	perror("shmget");
	return -1;
	}
	return 0;
}
