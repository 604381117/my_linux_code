#include"func.h"
#define N 10000000

pthread_mutex_t mutex;

void* thread(void* IN)  //无类型的指针，不能叫做空类型的指针
{
	int i;
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&mutex);
		*(int*)IN+=1;
		pthread_mutex_unlock(&mutex);
	}
	printf("pthread exit value=%d\n",(int)IN);
	return NULL;
}

int main()
{
	pthread_t id;
	int i,ret, *p=(int*)malloc(4);
	*p=0;
	ret=pthread_mutex_init(&mutex,NULL);
	if(ret!=0)
	{
		printf("pthread_mutex_init=%i\n",ret);
		exit(-1);
	}
	ret=pthread_create(&id,NULL,thread,p);
	if(ret!=0)
	{
		printf("pthread_creat ret=%i\n",ret);
		exit(-1);
	}
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&mutex);
		*p+=1;
		pthread_mutex_unlock(&mutex);
	}
	pthread_join(id,NULL);
	pthread_cancel(id);
	printf("main pthread exit value=%d\n",*p);
	return 0;
}
