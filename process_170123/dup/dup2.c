#include "func.h"

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int fda,fdb;
	fda=open(argv[1],O_RDWR);
	fdb=open(argv[2],O_RDWR);
	int fdb2=dup(fdb);
	int fda2=dup2(fda,fdb);
	printf("fda=%d,fdb=%d,fda2=%d,fdb2=%d\n",fda,fdb,fda2,fdb2);
	char buf[20]={0};
	read(fda,buf,sizeof(buf));
	printf("fda:%s\n",buf);
	bzero(buf,sizeof(buf));
	lseek(fda2,0,SEEK_SET);//让文件指针偏移到头部
	read(fda2,buf,sizeof(buf));
	printf("fda2:%s\n",buf);
	bzero(buf,sizeof(buf));
	read(fdb2,buf,sizeof(buf));
	printf("fdb2:%s\n",buf);
	bzero(buf,sizeof(buf));
	close(fda);
	close(fdb);
	close(fdb2);
	return 0;
}
