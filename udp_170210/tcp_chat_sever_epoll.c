#include"func.h"
#define N 100
#define M 5

int change_nonblock(int fd)
{
	int status=fcntl(fd,F_GETFL);
	status|=O_NONBLOCK;
	if(-1==fcntl(fd,F_SETFL,status))
	{
		perror("fcntl");
		return -1;
	}
	return 0;
}

int tcp_init(char* ip,char* port)
{
	int ret,sfd;
	if(-1==(sfd=socket(AF_INET,SOCK_STREAM,0)))
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in sev;
	bzero(&sev,sizeof(struct sockaddr_in));
	sev.sin_family=AF_INET;
	sev.sin_port=htons(atoi(port));
	sev.sin_addr.s_addr=inet_addr(ip);
	if(-1==(ret=bind(sfd,(struct sockaddr*)&sev,sizeof(struct sockaddr_in))))
	{
		perror("bind");
		return -1;
	}
	listen(sfd,M);
	return sfd;
}

int event_init(struct epoll_event *ev,int fd)
{
	bzero(ev,sizeof(struct epoll_event));
	ev->events=EPOLLIN|EPOLLET;
	if(0==fd)
		ev->data.fd=STDIN_FILENO;
	else
		ev->data.fd=fd;
	return 0;
}

int main(int argc,char **argv)
{
	if(3!=argc)
	{
		printf("erro args");
		return -1;
	}
	int i,ret,sfd,epfd,new_sfd=-1;
	sfd=tcp_init(argv[1],argv[2]);
	char buf[N]={0};
	struct sockaddr_in client;
	epfd=epoll_create(1);
	struct epoll_event event,evs[3];
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
		ret=epoll_wait(epfd,evs,3,-1);
		if(ret>0)
		{
			for(i=0;i<ret;i++)
   			{
	   			if(evs[i].data.fd==new_sfd)
				{
					while(1)
					{
						bzero(buf,sizeof(buf));
						ret=recv(new_sfd,buf,sizeof(buf),0);
						if(-1==ret && errno==EAGAIN)
						{
							break;  //读空缓冲区
						}else if(0==ret){
							printf("Good bye");
							close(new_sfd);
							event_init(&event,new_sfd);
							ret=epoll_ctl(epfd,EPOLL_CTL_DEL,new_sfd,&event);
							break;
							}
						printf("%s",buf);
					}
					printf("\n");
				}
	   			if(evs[i].data.fd==sfd)
				{	
					int addrlen=sizeof(client);
					if(-1==(new_sfd=accept(sfd,(struct sockaddr*)&client,&addrlen)))
					{
						perror("accept");
	   					exit(-1);
					}
					printf("success connect,client ip=%s port=%d\n",\
							inet_ntoa(client.sin_addr),ntohs(client.sin_port));
					change_nonblock(new_sfd);
					bzero(buf,sizeof(buf));
					event_init(&event,new_sfd);
					ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_sfd,&event);
	   			}
				if(0==evs[i].data.fd && evs[i].events==EPOLLIN)
				{
					bzero(buf,sizeof(buf));
					if((ret=read(STDIN_FILENO,buf,sizeof(buf)))<=0)
	   				{
						printf("Good bye\n");
						close(new_sfd);
						event_init(&event,new_sfd);
						epoll_ctl(epfd,EPOLL_CTL_DEL,new_sfd,&event);
						continue;
	   				}
					if(-1==(ret=send(new_sfd,buf,strlen(buf)-1,0)))
					{
						perror("send");
						exit(-1);
					}
				}
			}
		}
	}
	close(epfd);
	close(sfd);
	return 0;
}
