#include<stdio.h>
#include<stdlib.h>
int main()
{
	#ifdef x
		printf("x is defined!\n");
	#else
		printf("x is not defined\n");
	#endif
		printf("main exit\n");
}
	
