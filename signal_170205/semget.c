#include "func.h"

int main()
{
	int semid;//信号量集合ID
	semid=semget(1234,1,IPC_CREAT|0600);
	if(-1==semid)
	{
		perror("semget");
		exit(-1);
	}
	int ret;
	ret=semctl(semid,0,SETVAL,1);
	if(-1==ret)
	{
		perror("semctl");
		exit(-1);
	}
	ret=semctl(semid,0,GETVAL);
	if(-1==ret)
	{
		perror("semctl");
		exit(-1);
	}
	
	printf("the value=%d\n",ret);
	semctl(semid,0,IPC_RMID);
	if(-1==ret)
	{
		perror("semctl");
		exit(-1);
	}
	return 0;
}
