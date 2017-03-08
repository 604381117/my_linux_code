#include <stdio.h>

int main()
{
	int age;
	float score;
	char name[20]={0};
	char *p="zhangsan 19 91.5";
	sscanf(p,"%s%d%f",name,&age,&score);
	printf("name=%s,age=%d,score=%6.2f\n",name,age,score);
	return 0;
}
