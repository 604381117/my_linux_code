#include"func.h"
int main(int argc,char **argv)
{             
	if(3!=argc)
	{
		printf("error args");
		return -1;
	}
	int fdr,fdw;
	fdr=open(argv[1],O_RDONLY);//open fifo1 read pot
	if(-1==fdr)
	{
		perror("open1r");
		return -1;
	}
	fdw=open(argv[2],O_WRONLY);//open fifo2 write pot
	if(-1==fdw)
	{
		perror("open2w");
		return -1;
	}
	printf("open pipe sucess:\n");
	char buf[20]={0};
	int ret;
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(fdr,&rdset);
		ret=select(fdr+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&rdset))
			{
				memset(buf,0,sizeof(buf));
				if(read(fdr,buf,sizeof(buf)-1)>0)
				{
					puts(buf);
				}else{
					break;
				}
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				if(read(STDIN_FILENO,buf,sizeof(buf))>0)
				{
					write(fdw,buf,strlen(buf)-1);
				}else{
					break;
				}
			}
		}
	}
	close(fdr);
	return 0;
}
