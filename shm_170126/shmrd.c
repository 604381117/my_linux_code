#include"func.h"

int main()
{
		int shmid=shmget((key_t)5080,sizeof(struct text),0600|IPC_CREAT);
		struct text* ptext=(struct text*)shmat(shmid,NULL,0);
		ptext->useful=0 ;
		while(1)
		{
				if(ptext->useful==1)
				{
						write(STDOUT_FILENO,ptext->buf,strlen(ptext->buf));
						ptext->useful=0 ;
						if(strncmp("end",ptext->buf,3)==0)
						{
								break ;
						}
				}
				sleep(1);
		}
		shmdt((void*)ptext);
		shmctl(shmid,IPC_RMID,0);
		return 0 ;
}
