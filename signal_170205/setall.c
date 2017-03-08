#include "func.h"

int main()
{
	int semid;//信号量集合ID
	semid=semget(1234,3,IPC_CREAT|0600);
	if(-1==semid)
	{
		perror("semget");
		exit(-1);
	}
	unsiged int a[3]={23,67,3}
	int ret;
	ret=semctl(semid,0,SETALL,a);
	if(-1==smctl)
	{
		perror("smctl");
		exit(-1);
	}
	printf("");
	struct semid ds
	return 0;
}
