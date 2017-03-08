#include"func.h"

int main()
{
	int port=0x6357;
	int nport;
	nport=htons(port);
	printf("nport=%x",nport);
	return 0;
}
