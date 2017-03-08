#include"func.h"
#define N 5    //容纳客户端数
#define M 100  //读取缓存大小

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

	//主机字节序转网络字节序
	sever.sin_port=htons(atoi(argv[2]));

	//1.unsigned long int,点分十进制转二进制
	//2.INADDR_ANY系统自动填入本机IP
	//3.unsigned long int,点分十进制转二进制
	sever.sin_addr.s_addr=inet_addr(argv[1]);
	int ret=bind(sfd,(struct sockaddr*)&sever,sizeof(sever));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	if(-1==listen(sfd,N))
	{
		perror("listen");	
		return -1;
	}

	struct sockaddr_in client;
	char buf[M]={0};
	int new_sfd=-1;
	bzero(&client,sizeof(client));//memset(&client,0,sizeof(client));
	fd_set rdset,tempset;
	FD_ZERO(&tempset);
	FD_SET(STDIN_FILENO,&tempset);
	FD_SET(sfd,&tempset);
	while(1)
	{
		FD_ZERO(&rdset);
		memcpy(&rdset,&tempset,sizeof(fd_set));
		ret=select(N+3,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(new_sfd,&rdset))
			{
				memset(buf,0,sizeof(buf));
				if(-1==(ret=recv(new_sfd,buf,sizeof(buf),0)))
				{
					perror("recv");
					return 0;
				}else if(0==ret){
					printf("Good bye.\n");
					close(new_sfd);
					FD_CLR(new_sfd,&tempset);
					continue;
				}
				puts(buf);
			}
			if(FD_ISSET(sfd,&rdset))
			{						
				int addlen=sizeof(client);
				new_sfd=accept(sfd,(struct sockaddr*)&client,&addlen);
				if(-1==new_sfd)
				{
					perror("accept");
					return -1;
				}
				printf("Clien ip:%s,port:%d success connect\n",\
				inet_ntoa(client.sin_addr),ntohs(client.sin_port));
				FD_SET(new_sfd,&tempset);
			}
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				bzero(buf,sizeof(buf));
				ret=read(STDIN_FILENO,buf,sizeof(buf));
				if(ret<=0)
				{
					printf("Good bye.\n");
					close(new_sfd);
					FD_CLR(new_sfd,&tempset);
					continue;
				}
				if(-1==send(new_sfd,buf,strlen(buf)-1,0))
				{
					perror("send");
					return -1;
				}
			}
		
		}
	}
	close(sfd);
	return 0;
}
