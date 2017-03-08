#include"func.h"

int main()
{
	int semid;
	semid=semget(IPC_PRIVATE,1,IPC_CREAT|0666);
	if(-1==semid)
	{
		perror("semget");
		exit(-1);
	}
	if(!fork())
	{
		struct sembuf sv;
		memset(&sv,0,sizeof(struct sembuf));
		sv.sem_num=0;
		sv.sem_op=1;
		sv.sem_flg=SEM_UNDO;
		//union semun arg;
		int val=0;
		semctl(semid,0,SETALL,val);
		while(1)
		{
			semop(semid,&sv,1);
			printf("productor total number:%d\n",semctl(semid,0,GETVAL));
			sleep(1);
		}
	}else{
		sleep(2);
		struct sembuf sp;
		memset(&sp,0,sizeof(struct sembuf));
		sp.sem_num=0;
		sp.sem_op=-1;
		sp.sem_flg=SEM_UNDO;
		while(1)
		{
			semop(semid,&sp,1);
			printf("customer total number:%d\n",semctl(semid,0,GETVAL));
			sleep(2);
		}
	}
}
