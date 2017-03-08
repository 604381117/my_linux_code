#include"func.h"
int main()
{
	signal(SIGINT,SIG_DFL);
	while(1)
		sleep(1);
	return 0;
}
