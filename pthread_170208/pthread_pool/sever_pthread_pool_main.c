#include"sever_pthread_pool_func.h"

void *threadfunc(void* p)
{
	pfac pf=(pfac)p;
	pque pq=&pf->que;
	pNode pn;//指向new_sfd存储的结点
	while(1)
	{
		pthread_mutex_lock(&pq->mutex);
		if(0==pq->size)
		{
			pthread_cond_wait(&pf->cond,&pq->mutex);
		}
		que_get(pq,&pn);
		pthread_mutex_unlock(&pq->mutex);
		send_file(pn->new_sfd);
		free(pn);
	}

}

int main(int argc,char **argv)
{
	if(5!=argc)
	{
		printf("error args\n");
		return -1;
	}
	fac f;
	bzero(&f,sizeof(fac));
	f.pthnum=atoi(argv[3]);
	f.cap=atoi(argv[4]);
	factory_init(&f,threadfunc);
	factory_start(&f);
	int sfd=tcp_init(argv[1],argv[2]);
	listen(sfd,f.cap);
	int new_sfd;
	while(1)
	{
		new_sfd=accept(sfd,NULL,NULL);
		que_add(&f.que,new_sfd);
		pthread_cond_signal(&f.cond);
	}
	return 0;
}
