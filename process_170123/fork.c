#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	pid_t pid;
	char *p=(char*)malloc(10);
	memset(p,0,10);
	strcpy(p,"hello");
	pid=fork();       //返回2个值，第一次由父进程返回子进程ID，第二次由子进程返回0。
	if(0==pid)
	{
		printf("i am child pid=%d,ppid=%d\n",getpid(),getppid());
		printf("child=%s\n",p);
		sleep(1);
		printf("after child=%s\n",p);
		return 0;
	}else{
		printf("i am parent,pid=%d,childpid=%d\n",getpid(),pid);
		printf("parent=%s\n",p);
		strcpy(p,"world");
		sleep(5);
		printf("after parent=%s\n",p);
		return 0;
	}
}
