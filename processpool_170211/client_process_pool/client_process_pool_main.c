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
	long size;
	Recvfilesize(sfd,&size);
	int fd;
	if(-1==(fd=open(buf,O_RDWR|O_CREAT,0666)))
	{
		perror("open");
		return -1;
	}
	long total=0;
	double i=5,j;
	time_t first,second;
	first=time((time_t*)NULL);
	while(1)
	{
		recv_n(sfd,(char*)&len,4);
		total+=len;
		bzero(buf,sizeof(buf));
		if(len>0)
		{
			recv_n(sfd,buf,len);
			write(fd,buf,len);
		}else{
			break;
		}
		second=time((time_t*)NULL);
		j=difftime(second,first);
		if(j>i)
		{
			printf("%2.0f%%......\n",(float)total/size*100);
			i+=5;
		}
	}
	close(fd);
	close(sfd);
	return 0;
}
