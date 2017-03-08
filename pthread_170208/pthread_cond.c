#include"func.h"

void *threadfunc(void *p)
{
	pthd d=(pthd)p;
	printf("i am child pthread,i will wait\n");
	pthread_mutex_lock(&d->mutex);
	printf("accept signal successs!\n");
	int ret=pthread_cond_wait(&d->cond,&d->mutex);
	if(ret!=0)
	{
		printf("pthread_cond_wait=%d\n",ret);
		return (void*)-1;
	}
	pthread_mutex_unlock(&d->mutex);
	printf("i am child pthread,i am wakeup\n");
	pthread_exit(NULL);
}

int main()
{
	thd d;
	pthread_mutex_init(&d.mutex,NULL);
	int ret=pthread_cond_init(&d.cond,NULL);
	if(ret!=0)
	{
		printf("pthread_cond_init=%d\n",ret);
		return -1;
	}
	pthread_t thid;
	pthread_create(&thid,NULL,threadfunc,&d);
	printf("ccreate success\n");
	usleep(1000000);
	pthread_cond_signal(&d.cond); //让条件变量成立
	pthread_join(thid,NULL);
	return 0;
}
