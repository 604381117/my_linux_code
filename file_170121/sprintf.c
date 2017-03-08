#include <stdio.h>

int main()
{
	int age=20;
	float score=98.5;
	char c[50]={0};
	sprintf(c,"I am lele,age=%d,score=%6.2f",age,score);
	puts(c);
	return 0;
}
