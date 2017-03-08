#include<stdio.h>

int main(int argc,char **argv)
{
	int i,j,sum;
	i=atoi(argv[1]);
	j=atoi(argv[2]);
	sum=i+j;
	printf("sum=%d\n",sum);
	return 1;
}
