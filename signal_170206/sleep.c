#include"func.h"

int main()
{
	
	//alarm(3); 任何信号到来都会唤醒sleep
	sleep(10);//sleep内部使用alar实现的
	return 0;

}
