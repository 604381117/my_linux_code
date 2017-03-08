#include"func.h"

int main()
{
	char s[10]={0};
	sprintf(s,"%d\n",getpid());
	puts(s);
	printf("%d\n",strlen(s));
	int a=atoi(s);
	printf("%d",a);
	return 0;
}


