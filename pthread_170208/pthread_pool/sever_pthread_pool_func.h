#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/uio.h>
#include <sys/epoll.h>

#define FILENAME "ubuntu-15.04-desktop-i386.iso"
typedef void* (*pthfunc)(void*);

typedef struct traindata{
	int len;        //代表其后的长度
	char buf[1000]; //真实数据长度
}tda,*ptda;

typedef struct list{                                                                                  
	int new_sfd;
	struct list *pnext;
}Node,*pNode;

typedef struct work_que{
	pNode phead,ptail;
	pthread_mutex_t mutex;//监控
	int size;//标示队列的实时长度
}que_t,*pque;

typedef struct factory{
	int pthnum;//创建的线程数目
	pthread_t *pth;//指向pthread数组，数组内存放的是所有线程id
	pthread_cond_t cond;
	pthfunc entrance;//调用此函数创建子线程
	que_t que;
	int cap; //线程最大容量
	int start;//0代表未启动，1代表已启动
}fac,*pfac;

void factory_init(pfac,pthfunc);//同时将线程函数初始化
void que_init(pque);
void factory_start(pfac);//创建线程
void que_get(pque,pNode*);
int send_file(int);
int send_n(int,char*,int);
int send_filesize(int,int);
int tcp_init(char*,char*);
int send_fd(int,int);
void que_add(pque,int);


