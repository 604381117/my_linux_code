#include"func.h"
#define N 100

int udp_init(char* ip,char* port)
{
	int sfd,addrlen;
	if(-1==(sfd=socket(AF_INET,SOCK_DGRAM,0)))
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in sever;
	addrlen=sizeof(sever);
	bzero(&sever,sizeof(sever));
	sever.sin_family=AF_INET;
	sever.sin_addr.s_addr=inet_addr(ip);
	sever.sin_port=htons(atoi(port));
	if(-1==bind(sfd,(struct sockaddr*)&sever,sizeof(sever)))
	{
		perror("bind");
		return -1;
	}
	return sfd;
}

int main(int argc,char **argv)
{
	if(3!=argc)
	{
		printf("erro args");
		return -1;
	}
	int sfd,i,ret,epfd;
	char buf[N]={0};
	struct sockaddr_in client;
	struct epoll_event event,evs[2];
	sfd=udp_init(argv[1],argv[2]);
	epfd=epoll_create(1);
	bzero(&event,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=sfd;
	if(-1==(ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event)))
	{
		perror("epoll_ctl");
		return -1;
	}
	bzero(&event,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=STDIN_FILENO;
	if(-1==(ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event)))
	{
		perror("epoll_ctl");
		return -1;
	}
	int flag=1;
	while(1)
	{	
		bzero(evs,sizeof(evs));
		ret=epoll_wait(epfd,evs,2,-1);
		if(ret>0)
		{	
			for(i=0;i<ret;i++)
			{
				if(evs[i].data.fd==sfd)
				{
					bzero(buf,sizeof(buf));
					int addlen=sizeof(client);
					ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&addlen);
					if(-1==ret)
					{
						perror("recvfrom");
						return -1;
					}else if(0==ret){
						printf("Good bye\n");
						bzero(&event,sizeof(event));
						event.events=EPOLLIN;
						event.data.fd=sfd;
						ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
						break;
					}
					if(1==flag)
					{
						printf("success connect,client ip=%s port=%d\n",\
							inet_ntoa(client.sin_addr),ntohs(client.sin_port));
						flag=0;
					}
					puts(buf);
				}
				if(0==evs[i].data.fd && evs[i].events==EPOLLIN)
				{	
					bzero(buf,sizeof(buf));
					if(0==(ret=read(STDIN_FILENO,buf,sizeof(buf))))
					{
						printf("Good bye\n");
						close(sfd);
						bzero(&event,sizeof(event));
						event.events=EPOLLIN;
						event.data.fd=sfd;
						epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
						continue;
					}
					ret=sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&client,sizeof(client));
					if(-1==ret)
					{
						perror("sendto");
						return -1;
					}
				}
			}
		}
	}
	close(sfd);
	return 0;
}
