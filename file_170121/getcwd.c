#include <unistd.h>
#include <stdio.h>
int main()
{
	char buf[50]={0};
	char *p;
	p=getcwd(buf,sizeof(buf));
	if(NULL==p)
	{
		perror("getcwd");
		return -1;
	}
	p=getcwd(NULL,0);
	printf("%s\n",p);
	return 0;
}
