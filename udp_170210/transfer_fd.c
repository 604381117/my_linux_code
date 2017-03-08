#include"func.h"
#define N 15
void send_fd(int fdw,int fd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	struct iovec iov[2];
	char buf[N]="wang dao-";
	char buf1[N]="belief dream";
	iov[0].iov_base=buf;
	iov[0].iov_len=9;
	iov[1].iov_base=buf1;
	iov[1].iov_len=12;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr*)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	*(int*)CMSG_DATA(cmsg)=fd;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	int ret=sendmsg(fdw,&msg,0);
	if(-1==ret)
	{
		perror("sendmsg");
		return;
	}
}

void recv_fd(int fdr,int *fd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	struct iovec iov[2];
	char buf[N]="wang dao-";
	char buf1[N]="belief dream";
	iov[0].iov_base=buf;
	iov[0].iov_len=9;
	iov[1].iov_base=buf1;
	iov[1].iov_len=12;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr*)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	int ret=recvmsg(fdr,&msg,0);
	if(-1==ret)
	{
		perror("sendmsg");
		return;
	}
	*fd=*(int*)CMSG_DATA(cmsg);
}

int main()
{
	int fds[2];
	socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
	if(!fork())
	{	
		close(fds[1]);
		int fd;
		recv_fd(fds[0],&fd);
		printf("fd=%d\n",fd);
		char buf[100]={0};
		read(fd,buf,sizeof(buf));
		printf("buf=%s\n",buf);
		close(fds[0]);
		exit(0);
	}else{
		close(fds[0]);
		int fd;
		fd=open("transfer_fd_from",O_RDWR|O_CREAT,0777);
		if(-1==fd)
		{
			perror("open");
			exit(-1);
		}
		printf("parent proccess fd=%d\n",fd);
		send_fd(fds[1],fd);
		wait(NULL);
		return 0;
	}
}

