#include"client_process_pool_func.h"

int main(int argc,char **argv)
{
	if(3!=argc)
	{
		printf("error args");
		return -1;
	}
	int sfd;
	sfd=tcp_init(argv[1],argv[2]);
	char buf[1000]={0};
	int len;
	recv_n(sfd,(char*)&len,4);
	printf("len=%d\n",len);
	recv_n(sfd,buf,len);
	Recvfilesize()
	int fd;
	if(-1==(fd=open(buf,O_RDWR|O_CREAT,0666)))
	{
		perror("open");
		return -1;
	}
	while(1)
	{
		recv_n(sfd,(char*)&len,4);
		bzero(buf,sizeof(buf));
		if(len>0)
		{
			recv_n(sfd,buf,len);
			write(fd,buf,len);
		}else{
			break;
		}
	}
	close(fd);
	close(sfd);
	return 0;
}
