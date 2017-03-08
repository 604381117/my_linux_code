#include"func.h"
int main(int argc,char **argv)
{
	printf("i will execl\n");
	execl("./add","add","3","4",NULL);
	printf("you cant see me\n");
	return 0;
}

