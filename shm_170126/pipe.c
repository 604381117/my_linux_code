#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
int main()
{
	int ret,fds[2];
	char buf[50]={0};
	pipe(fds);
	if(!fork())
	{
		close(fds[0]);
		ret=write(fds[1],"Hello",6);
		if(ret<=0)
		{	
			perror("write");
			return -1;
		}
		close(fds[1]);
		exit(0);
	}else{
		close(fds[1]);
		ret=read(fds[0],buf,sizeof(buf));
		puts(buf);
		wait(NULL);
		close(fds[0]);
		return 0;
	}
}
