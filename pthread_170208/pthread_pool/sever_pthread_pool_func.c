#include"sever_pthread_pool_func.h"

void que_add(pque p,int new_sfd)
{
	pNode pnew=(pNode)calloc(1,sizeof(Node));
	pnew->new_sfd=new_sfd;
	pthread_mutex_lock(&p->mutex);
	if(NULL==p->ptail)
	{
		p->phead=pnew;
		p->ptail=pnew;
	}else{
		p->ptail->pnext=pnew;
		p->ptail=pnew;
	}
	p->size++;
	pthread_mutex_unlock(&p->mutex);
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

void que_get(pque p,pNode* pn)
{
	*pn=p->phead;
	p->phead=p->phead->pnext;
	p->size--;
}

void factory_start(pfac p)
{
	int i;
	if(0==p->start)
	{
		for(i=0;i<p->pthnum;i++)
		{
			pthread_create(&p->pth[i],NULL,p->entrance,p);
		}
		p->start=1;
	}else{
		printf("factory had started\n");
	}
}

void que_init(pque p)
{
	bzero(p,sizeof(que_t));
	pthread_mutex_init(&p->mutex,NULL);
}

void factory_init(pfac p,pthfunc entrance)
{
	p->pth=(pthread_t*)calloc(p->pthnum,sizeof(pthread_t));
	p->entrance=entrance;//线程入口函数初始化
	pthread_cond_init(&p->cond,NULL);
	que_init(&p->que);
	p->start=0;
}

