#include"func.h"
int main()
{
	if(!fork())
	{
	while(1);
	}else{
	printf("i am parent\n");
	exit(0);
	}
	return 0;
}
