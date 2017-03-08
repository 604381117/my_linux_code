#include"func.h"
#define N 10000000

pthread_mutex_t mutex;

void* thread(void* p)  //无类型的指针，不能叫做空类型的指针
{
	int *q=(int*)p;
	int i;
	for(i=0;i<N;i++)
	{
	pthread_mutex_lock(&mutex);
	*q+=1;
	pthread_mutex_unlock(&mutex);
	}
	printf("the thread %d creat success,\n",*q);
	//pthread_exit(NULL);
	return NULL;
}

int main()
{
	pthread_t id;
	//printf("id=%d\n",id);
	int i,ret;
	int *p=(int*)malloc(4);
	*p=0;
	pthread_mutexattr_t mattr;
	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_settype(&mattr,PTHREAD_MUTEX_RECURSIVE);
	ret=pthread_mutex_init(&mutex,&mattr);
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
	pthread_mutex_lock(&mutex);
	*p+=1;
	pthread_mutex_unlock(&mutex);
	}

	pthread_join(id,NULL);
	printf("*p=%d\n",*p);
	printf("main thread input here\n");
	return 0;
}
