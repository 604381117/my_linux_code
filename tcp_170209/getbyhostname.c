#include"func.h"

int main(int argc,char **argv)
{
	struct hosent *hp;
	if(2!=argc)
	{
		printf("error args");
		return -1;
	}
	hp=gethostbyname(argv[1]);
	if(NULL=hp)
	{
		printf("gethostbyname h_error=%d\n",h_errono);
		return -1;
	}
	printf("h_name=%s\n",hp->h_name);
	char **p;
	p=hp->h_aliases;
	for(;p!=NULL;p++)
	{
		printf("h_aliases=%s\n",*);
	}
	printf("h_length=%d\n",hp->h_length);
	char ip[16]={0};
	inet
}
