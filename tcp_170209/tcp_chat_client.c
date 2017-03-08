#include"func.h"
#define M 100   //读写缓存大小

int main(int argc,char **argv)
{
	if(3!=argc)
	{
		printf("error args");
		return -1;
	}
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		
		return -1;
	}
	
	struct sockaddr_in sever;
    memset(&sever,0,sizeof(sever));
	sever.sin_family=AF_INET;
    sever.sin_port=htons(atoi(argv[2]));
	sever.sin_addr.s_addr=inet_addr(argv[1]);
	int ret=connect(sfd,(struct sockaddr*)&sever,sizeof(sever));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	ret=send(sfd,"from client:",12,0);
	if(-1==ret)
	{
		perror("send");
		return -1;
	}

	char buf[M];
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(sfd,&rdset);
		ret=select(sfd+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				bzero(buf,sizeof(buf));
				ret=read(STDIN_FILENO,buf,sizeof(buf));
				if(ret<=0)
				{
					printf("Good bye.\n");
					break;
				}
				if(-1==send(sfd,buf,strlen(buf)-1,0))
				{
					perror("send");
					return -1;
				}
			}
			if(FD_ISSET(sfd,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=recv(sfd,buf,sizeof(buf),0);
				if(-1==ret)
				{
					perror("recv");
					return -1;
				}else if(0==ret){
					printf("Good bye.\n");
					break;
				}
				printf("%s\n",buf);
			}
		}
	}
	close(sfd);		
	return 0;
}
