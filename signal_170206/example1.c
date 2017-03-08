#include"func.h"

void handle(num)
{
	printf("signumber=%d\n",num);
}

int main()
{
	struct sigaction st;
	st.sa_handler=handle;
	st.sa_flags=0;
	sigaction(SIGINT,&st,NULL);
	while(1)
	{
		sleep(1);
	}
}
