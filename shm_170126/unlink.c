#include"func.h"

int main(int argc,char **argv)
{
	if(2!=argc)
	{
	printf("error args\n");
	return -1;
	}
	int ret;
	ret=unlink(argv[1]);
	if(-1==ret)
	{
	perror("unlink");
	return -1;
	}
	return 0;
}
