#include"func.h"

void* thread(void* p)  //无类型的指针，不能叫做空类型的指针
{
	char *q=(char*)malloc(10);
	strcpy(q,"asdj sdg");
	return q;
}

int main()
{
	pthread_t id;
	//printf("id=%d\n",id);
	int i,ret;
	ret=pthread_create(&id,NULL,thread,NULL);
	if(ret!=0)
	{
		printf("pthread_creat ret=%i\n",ret);
		exit(-1);
	}
	char *p;
	ret=pthread_join(id,(void**)&p);
	if(ret!=0)
	{
		printf("pthread_join ret=%i\n",ret);
		exit(-1);
	}
	printf("*p=%s\n",p);
	return 0;
}

