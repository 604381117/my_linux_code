#include"func.h"

//cancel子线程
void* thread(void* p)  //无类型的指针，不能叫做空类型的指针
{
	printf("thread create success\n");
	sleep(2);
	printf("i can not be here");
	return NULL;
}

int main()
{
	pthread_t id;
	int i,ret;
	ret=pthread_create(&id,NULL,thread,NULL);
	if(ret!=0)
	{
		printf("pthread_creat ret=%i\n",ret);
		exit(-1);
	}
	pthread_cancel(id);
	if(ret!=0)
	{
		printf("pthread_creat ret=%i\n",ret);
		exit(-1);
	}
	ret=pthread_join(id,NULL);
	if(ret!=0)
	{
		printf("pthread_creat ret=%i\n",ret);
		exit(-1);
	}
	return 0;
}
