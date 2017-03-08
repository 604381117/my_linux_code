#include"func.h"

void change_unblock(int fd)
{
	int status=fcntl(fd,F_GETFL);
	status=status|O_NONBLOCK;//~
	int ret=fcntl(fd,F_SETFL,status);
	if(-1==ret)
	{
		perror("fcntl");
		return;
	}
}

int main()
{
	char buf[100]={0};
	change_unblock(0);
	int ret=read(0,buf,sizeof(buf));
	printf("buf=%s\nret=%d\nerrono=%d",buf,ret,errno);
	return 0;
}
