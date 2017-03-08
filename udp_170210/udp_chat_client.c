#include"func.h"
#define N 100

int udp_init(struct sockaddr_in *sever,char* ip,char* port)
{
	int sfd;
	socket(AF_INET,SOCK_DGRAM,0);
	if(-1==(sfd=socket(AF_INET,SOCK_DGRAM,0)))
	{
		perror("socket");
		return -1;
	}
	bzero(sever,sizeof(struct sockaddr_in));
	sever->sin_family=AF_INET;
	sever->sin_addr.s_addr=inet_addr(ip);
	sever->sin_port=htons(atoi(port));
	return sfd;
}

int main(int argc,char **argv)
{
	if(3!=argc)
	{
		printf("erro args");
		return -1;
	}
	char buf[N]={0};
	int i,ret,sfd,epfd;
	struct sockaddr_in sever;
	struct epoll_event event,evs[2];
	sfd=udp_init(&sever,argv[1],argv[2]);
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
					int addlen=sizeof(sever);
					ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&sever,&addlen);
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
					puts(buf);
				}
				if(0==evs[i].data.fd && evs[i].events==EPOLLIN)
				{
					bzero(buf,sizeof(buf));
					if(0==(ret=read(STDIN_FILENO,buf,sizeof(buf))))
					{
						printf("Good bye\n");
						event.events=EPOLLIN;
						event.data.fd=sfd;
						epoll_ctl(epfd,EPOLL_CTL_DEL,sfd,&event);
						continue;
					}
					ret=sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&sever,sizeof(sever));
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
