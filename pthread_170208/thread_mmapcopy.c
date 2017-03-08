#include"func.h"
#define N 10

char *pfrom,*pto;
int size;            //获取文件大小 

void *threadfunc(void *p)
{
	int star=(int)p*(size/N);
	memcpy(pto+star,pfrom+star,size/N);
	return NULL;
}

size_t GetFileSize(int fd)
{
	struct stat buf;
	int ret=fstat(fd,&buf);
	if(-1==ret)
	{
		perror("fstat");
		return (size_t)-1;
	}
	return buf.st_size;
}

void GetRunTime()
{
	time_t t;
	time(&t);
	struct tm *pTm=gmtime(&t);
	printf("%04d-%02d-%02d %02d:%02d:%02d\n",\
	(1900+pTm->tm_year),(1+pTm->tm_mon),pTm->tm_mday,\
	(8+pTm->tm_hour),pTm->tm_min,pTm->tm_sec);
}

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("error args");
		return -1;
	}

	GetRunTime();
	int i=0,ffrom,fto;
	ffrom=open(argv[1],O_RDWR,0666);
	size=(int)GetFileSize(ffrom);
	printf("from:%s to:target size=%d Byte\n",argv[1],size);
	fto=open("target",O_RDWR|O_CREAT,0666);
	if(-1==ffrom||-1==fto)
	{
		perror("open ffrom");
		return -1;
	}

	int ret=ftruncate(fto,size);
	if(ret==-1)
	{
		perror("ftruncate");
		return -1;
	}

	pfrom=(char*)mmap(NULL,size,PROT_READ,MAP_SHARED,ffrom,0);
	pto=(char*)mmap(NULL,size,PROT_WRITE,MAP_SHARED,fto,0);
	if((char*)-1==pfrom||(char*)-1==pto)
	{
		perror("mmap failed");
		return -1;
	}

	pthread_t id[N];
	for(;i<N;i++)
	{
		ret=pthread_create(&id[i],NULL,threadfunc,(void*)i);
		if(ret!=0)
		{
			printf("pthread_create %d",ret);
			return -1;
		}
	}
	for(i=0;i<N;i++)
		pthread_join(id[i],NULL);
	
	if(-1==munmap(pfrom,size)||-1==munmap(pto,size))
	{
		perror("munmap");
		return -1;
	}
	
	char buf[4096];
	GetRunTime();
	printf("after 5 second print...\n");
	sleep(5);
	do
	{
		ret=read(fto,buf,sizeof(buf));
		write(1,buf,sizeof(buf));
	}while(ret>0);
	close(ffrom);
	close(fto);
	return 0;
}
