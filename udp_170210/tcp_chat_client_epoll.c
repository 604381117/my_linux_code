#include"func.h"
#define N 100

int tcp_init(char* ip,char* port)                     
{
	int ret,sfd;
	if(-1==(sfd=socket(AF_INET,SOCK_STREAM,0)))
    {   
	    perror("socket");
		return -1; 
	}
	struct sockaddr_in sever;
	bzero(&sever,sizeof(struct sockaddr_in));
	sever.sin_family=AF_INET;
	sever.sin_addr.s_addr=inet_addr(ip);
	sever.sin_port=htons(atoi(port));
	ret=connect(sfd,(struct sockaddr*)&sever,sizeof(sever));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	return sfd;
}

int event_init(struct epoll_event *ev,int fd)
{
	bzero(ev,sizeof(struct epoll_event));
	ev->events=EPOLLIN|EPOLLET;
	if(0==fd)
	{
		ev->events=STDIN_FILENO;
	}else{
		ev->data.fd=fd;
	}
	return 0;
}

int main(int argc,char **argv)
{
	if(3!=argc)
	{
		printf("error args");
		return -1;
	}
	int ret,i,epfd,sfd;
	sfd=tcp_init(argv[1],argv[2]);
	struct epoll_event event,evs[2];
	char buf[N]={0};
	epfd=epoll_create(1);
	event_init(&event,sfd);
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}
	event_init(&event,0);
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	if(-1==ret)
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
					if(-1==(ret=recv(sfd,buf,sizeof(buf),0)))
					{
						perror("recv");
						return -1;
					}else if(0==ret){
						printf("Good bye\n");
						event_init(&event,sfd);
						ret=epoll_ctl(epfd,EPOLL_CTL_DEL,sfd,&event);
						{
							perror("epoll_ctl");
							return -1;
						}
						break;
					}
					puts(buf);
				}
				if(evs[i].data.fd==0)
				{
					bzero(buf,sizeof(buf));
					ret=read(STDIN_FILENO,buf,sizeof(buf));
					if(ret<=0)
					{
						printf("Good bye\n");
						event_init(&event,sfd);
						ret=epoll_ctl(epfd,EPOLL_CTL_DEL,sfd,&event);
						if(-1==ret)
						{
							perror("epoll_ctl");
							return -1;
						}
						break;
					}
					ret=send(sfd,buf,strlen(buf)-1,0);
					if(-1==ret)
					{
						perror("send");
						return -1;
					}
				}
			}
		}
	}
	close(epfd);
	close(sfd);
	return 0;
}
