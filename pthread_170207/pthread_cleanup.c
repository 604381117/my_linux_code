#include"func.h"

void cleanup(void *q)
{
	//int *i=(int*)p;
	printf("cleanup func %d\n",(int)q);
}

//pthread_cancel/pthreadexit(NULL)
void* thread(void *p)
{
	pthread_cleanup_push(cleanup,(void*)1);
	pthread_cleanup_push(cleanup,(void*)2);
	pthread_cleanup_push(cleanup,(void*)3);
	sleep(3);
	printf("i am wake\n");
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);//弹清理函数栈，并执行
	//pthread_cancel(id);
	return NULL;
}

int main()
{
	pthread_t id;
	int ret=pthread_create(&id,NULL,thread,NULL);
	if(ret!=0)
	{
		printf("pthread_create ret =%d\n",ret);
		return -1;
	}
	pthread_join(id,NULL);
	return 0;
}
