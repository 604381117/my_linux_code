 /// @file    1kw.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-05 10:06:46
 ///
 
#include <iostream>
using std::cout;
using std::endl;
#include"func.h"

int main(int argc,char **argv)
{
	if(2!=argc)
	{
	printf("error args");
	return -1;
	}
	key_t k;
	k=ftok(argv[1],1);
	printf("k=%d\n",k);
	return 0;
}
