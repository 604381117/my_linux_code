#include"sever_process_pool_func.h"

int send_n(int fd,char *buf,int len)
{
	int total=0;
	int pos;
	while(total<len)
	{
		pos=send(fd,buf+total,len-total,0);
		total=total+pos;
	}
	return 0;
}

int send_filesize(int new_sfd,int fd)
{
	struct stat buf;
	int ret=fstat(fd,&buf);
	if(-1==ret)
	{
		perror("fstat");
		return (size_t)-1;
	}
	tda t;
	printf("size=%d Byte\n",buf.st_size);
	char bufs[20];
	bzero(bufs,sizeof(bufs));
	sprintf(bufs,"%d\n",buf.st_size);
	t.len=strlen(bufs);
	strcpy(t.buf,bufs);
	send_n(new_sfd,&t,4+t.len);
	return 0;
}

int send_file(int new_sfd)
{   
	tda t;
	memset(&t,0,sizeof(t));
	t.len=strlen(FILENAME);
	strcpy(t.buf,FILENAME);
	send_n(new_sfd,&t,4+t.len);
	int fd; 
	if(-1==(fd=open(FILENAME,O_RDONLY)))
	{ 
		perror("open");
		return -1;
	}
	send_filesize(new_sfd,fd);
	while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
	{   
		send_n(new_sfd,&t,4+t.len);
	}   
	t.len=0;
	send_n(new_sfd,&t.len,4);//发送结束符给客户端
	close(new_sfd);
	return 0;
}

int recv_fd(int fdr,int* fd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	struct iovec iov[2];
	char buf[20]="wang dao-"; 
	char buf1[20]="belief dream";
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
		perror("recvmsg");
		return -1;
	}
	*fd=*(int*)CMSG_DATA(cmsg);
	return 0;
}

int handle_request(int fdr)
{
	int new_sfd;
	short flag=1;
	while(1)
	{
		recv_fd(fdr,&new_sfd);
		printf("new_sfd=%d\n",new_sfd);
		send_file(new_sfd);
		write(fdr,&flag,sizeof(short));//?????
	}
	return 0;
}

int make_child(pcda pc,int count)
{
	int i,fds[2];
	pid_t pid;
	for(i=0;i<count;i++)
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		pid=fork();
		if(0==pid)
		{	
			close(fds[1]);
			handle_request(fds[0]);
		}
		pc[i].pid=pid;
		pc[i].fdw=fds[1];
		pc[i].busy=0;
		close(fds[0]);
	}
	return 0;
}

int send_fd(int fdw,int fd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	struct iovec iov[2];
	char buf[20]="wang dao-"; 
	char buf1[20]="belief dream";
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
		return -1;
	}
	return 0;
}

int event_init(struct epoll_event* ev,int fd)
{
	bzero(ev,sizeof(struct epoll_event));
	ev->events=EPOLLIN|EPOLLET;
	ev->events=EPOLLIN|EPOLLET;
	ev->data.fd=fd;
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
	ret=bind(sfd,(struct sockaddr*)&sev,sizeof(struct sockaddr_in));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	return sfd;
}

