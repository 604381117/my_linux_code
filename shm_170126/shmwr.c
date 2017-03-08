#include"func.h"

int main()
{
		int shmid=shmget((key_t)5080,sizeof(struct text),0600|IPC_CREAT);
		printf("%d\n",shmid);
		struct text* ptext=(struct text*)shmat(shmid,NULL,0);
		// ptext->useful = 0 ;
		while(1)
		{
				if(ptext->useful==0)
				{
						int iret=read(STDIN_FILENO,ptext->buf,1024);
						ptext->useful=1;
						if(strncmp("end",ptext->buf,3)==0)
						{
								break ;
						}
						//ptext ->useful = 0 ;
				}
				sleep(1);
		}
		shmdt((void *)ptext);
		return 0 ;
}
