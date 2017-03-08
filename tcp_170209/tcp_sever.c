#include"func.h"
int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("error args");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	if(-1==listen(sfd,10))
	{
		perror("listen");
		return -1;
	}
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	int new_sfd;
	int addlen=sizeof(client);
	new_sfd=accept(sfd,(struct sockaddr*)&client,&addlen);
	if(-1==new_sfd)
	{
		perror("new_sfd");
		return -1;
	}
	char buf[100]={0};
	if(-1==recv(new_sfd,buf,sizeof(buf),0))
	{
		perror("recv");
		return -1;
	}
	printf("%s\n",buf);
	if(-1==send(new_sfd,"i am sever",11,0))
	{
		perror("send");
		return -1;
	}
	return 0;
}
