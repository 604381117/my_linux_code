#include"client_process_pool_func.h"

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
	ret=connect(sfd,(struct sockaddr*)&sev,sizeof(sev));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	return sfd;
}

int recv_n(int fd,char *buf,int len)
{
	int total=0;
	int pos;
	while(total<len)
	{
		pos=recv(fd,buf+total,len-total,0);
		total=total+pos;
	}
	return 0;
}

