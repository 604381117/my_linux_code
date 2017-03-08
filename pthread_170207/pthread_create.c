#include"func.h"
#define N 10000000

void* thread(void* p)  //无类型的指针，不能叫做空类型的指针
{
	int *q=(int*)p;
	int i;
	for(i=0;i<N;i++)
		*q+=1;
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

	for(i=0;i<3;i++)
	{
	ret=pthread_create(&id,NULL,thread,p);
	if(ret!=0)
	{
		printf("pthread_creat ret=%i\n",ret);
		exit(-1);
	}
	}
	sleep(3);
	//pthread_join(id,NULL);
	printf("*p=%d\n",*p);
	printf("main thread input here\n");
	return 0;
}
