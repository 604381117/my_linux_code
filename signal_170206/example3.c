#include"func.h"

int g_iSeq = 0;
void SignHandlerNew(int iSignNo,siginfo_t *pInfo,void *pReserved)
{
	int iSeq = g_iSeq++;
	printf("%d Enter SignHandlerNew,signo:%d.\n",iSeq,iSignNo);
	sleep(3);
	printf("%d Leave SignHandlerNew,signo:%d\n",iSeq,iSignNo);
}

int main()
{
char szBuf[8] = {0};
int iRet = 0;
struct sigaction act;
act.sa_sigaction = SignHandlerNew;
act.sa_flags = SA_SIGINFO | SA_RESTART;
sigemptyset(&act.sa_mask);
sigaddset(&act.sa_mask, SIGQUIT);
sigaction(SIGINT,&act,NULL);
do{
	iRet = read(STDIN_FILENO,szBuf,sizeof(szBuf)-1);
	if(iRet < 0){
		perror("read fail");
		break;
	}
	szBuf[iRet] = 0;
	printf("Get: %s",szBuf);
}while(strcmp(szBuf,"quit\n") != 0);
return 0;

}
