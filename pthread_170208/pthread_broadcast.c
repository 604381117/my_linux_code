#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

typedef struct data{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}thread,*pthread;

void *threadfunc(void *p)
{
	int ret;
	pthread id=(pthread)p;
	printf("process id:%d,chlid pthread id:%lu be waiting!\n",getpid(),pthread_self());
	pthread_mutex_lock(&id->mutex);
	ret=pthread_cond_wait(&id->cond,&id->mutex);
	if(ret!=0)
	{
		printf("pthread_cond_wait=%d\n",ret);
		return (void*)-1;
	}
	printf("process id:%d,chlid pthread id:%lu signal coming!\n",getpid(),pthread_self());
	pthread_mutex_unlock(&id->mutex);
	printf("process id:%d,chlid pthread id:%lu is wakeup!\n",getpid(),pthread_self());
	pthread_exit(NULL);
}

int main(void)
{
	thread id;
	int i,ret;
	ret=pthread_mutex_init(&id.mutex,NULL);
	if(ret!=0)
	{
		printf("pthread_mutex_init=%d\n",ret);
		return -1;
	}
	ret=pthread_cond_init(&id.cond,NULL);
	if(ret!=0)
	{
		printf("pthread_cond_init=%d\n",ret);
		return -1;
	}
	pthread_t num[5];
	for(i=0;i<5;i++)
	{
		pthread_create(&num[i],NULL,threadfunc,&id);
		if(ret!=0)
		{
			printf("pthread_cond_init=%d\n",ret);
			return -1;
		}
		printf("%dth pthread create success,process!\n",i+1);
	}
	sleep(1);
	pthread_cond_broadcast(&id.cond); //让条件变量成立
	for(i=0;i<5;i++)
		pthread_join(num[i],NULL);
	pthread_mutex_destroy(&id.mutex);
	return 0;
}


