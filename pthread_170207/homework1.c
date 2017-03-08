#include"func.h"

void cleanfree(void *heapnum)
{
	printf("stack pop:%s\tfree success\n",(char*)heapnum);
	free(heapnum);
}

void* thread(void* IN)  //无类型的指针，不能叫做空类型的指针
{
	printf("pthread_creat IN value=%d\n",(int)IN);
	char *p=(char*)malloc(100);
	char *q=(char*)malloc(100);
	strcpy(p,"akdjhg  98qw7t ;l /ald tap o;lqywteo ;ilkayg");
	strcpy(q,"78904367 kahgd/,/,,//,.");
	pthread_cleanup_push(cleanfree,(void *)p);
	printf("stack push:%s\n",p);
	pthread_cleanup_push(cleanfree,(void *)q);
	printf("stack push:%s\n",q);
	sleep(2);
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
	pthread_exit((void*)999);
}

int main()
{
	pthread_t id;
	int ret;
	ret=pthread_create(&id,NULL,thread,(void*)666);
	if(ret!=0)
	{
		printf("pthread_creat ret=%i\n",ret);
		exit(-1);
	}
	int OUT;
	sleep(1);
	ret=pthread_join(id,(void**)&OUT);
	if(ret!=0)
	{
		printf("pthread_join ret=%i\n",ret);
		exit(-1);
	}
	printf("the main pthread accept OUT=%d\n",OUT);
	return 0;
}

