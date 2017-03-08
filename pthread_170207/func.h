#include <errno.h>
#include <unistd.h>
#include<stdio.h>
#include <sys/types.h> //头文件
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include<strings.h>
#include<string.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/sem.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
