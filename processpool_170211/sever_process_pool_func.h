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

#define FILENAME "linux-headers-3.19.0-15.tar.gz"
typedef struct childdata{
	pid_t pid;
	int fdw;		//
	short busy;     //0代表子进程忙碌,1代表非忙碌
}cda,*pcda;

typedef struct traindata{
	int len;        //代表其后的长度
	char buf[1000]; //真实数据长度
}tda,*ptda;

//子进程接收new_sfd并向客户端发送文件
int make_child(pcda,int);
int handle_request(int);
int recv_fd(int,int*);
int send_file(int);
int send_n(int,char*,int);

//主进程发送new_sfd给子进程
int tcp_init(char*,char*);
int event_init(struct epoll_event*,int);
int send_fd(int,int);
