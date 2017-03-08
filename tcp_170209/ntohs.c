#include"func.h"

int main()
{
	int port=0x6357;
	int nport;
	nport=htons(port);
	printf("nport=%x\n",nport);
	int a;
	a=ntohs(nport);
	printf("a=%x\n",a);
	return 0;
}
