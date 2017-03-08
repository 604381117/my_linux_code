#include"sever_process_pool_func.h"

int main(int argc,char **argv)
{
	if(4!=argc)
	{
		printf("error args");
		return -1;
	}
	int count=atoi(argv[3]);//进程数
	pcda pc=(pcda)calloc(count,sizeof(cda));
	make_child(pc,count);
	int sfd=tcp_init(argv[1],argv[2]);
	listen(sfd,count);
	int ret,epfd;
	struct epoll_event event,*evs;
	epfd=epoll_create(1);
	evs=(struct epoll_event*)calloc(count+1,sizeof(event));
	event_init(&event,sfd);
	if(-1==(ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event)))
	{
		perror("epoll_ctl_sfd");
		return -1;
	}
	int i;
	for(i=0;i<count;i++)
	{
		event.events=EPOLLIN;
		event.data.fd=pc[i].fdw;
		epoll_ctl(epfd,EPOLL_CTL_ADD,pc[i].fdw,&event);		
	}
	int ret1,j,new_sfd;
	short flag=1;
	while(1)
	{
		bzero(evs,(count+1)*sizeof(event));
		ret=epoll_wait(epfd,evs,count+1,-1);
		if(ret>0)
		{
			for(i=0;i<ret;i++)
			{
				if(evs[i].data.fd==sfd)
				{
					new_sfd=accept(sfd,NULL,NULL);
					for(j=0;j<count;j++)
					{
						if(0==pc[j].busy)	
						{
							send_fd(pc[j].fdw,new_sfd);
							pc[j].busy=1;
							break;
						}
					}
					close(new_sfd);
				}
				for(j=0;j<count;j++)
				{
					if(evs[i].data.fd==pc[j].fdw)
					{
						read(pc[j].fdw,&flag,sizeof(short));
						pc[j].busy=0;
					}
				}
			}
		}
	}
	close(sfd);
	close(epfd);
	return 0;
}
