 ///
 /// @file    remove.c
 /// @author  yy(jobyang@163.com)
 /// @date    2017-02-01 19:47:18
 ///
#include<errno.h>
#include<stdio.h>
void main()
{
	if(-1==remove("./test"))
	{
		perror("remove");
	}
}
