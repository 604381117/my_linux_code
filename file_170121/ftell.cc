 ///
 /// @file    fread.c
 /// @author  yy(jobyang@163.com)
 /// @date    2017-02-01 19:15:12
 ///
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#include<iostream>
using namespace std;

int main()
{
	FILE *fp=fopen("a.txt","w+");
	if(NULL==fp)
	{
		perror("open");
		exit(0);
	}
	char c='\0';
	while((c=fgetc(stdin))!='#')
		fputc(c,fp);
	fseek(fp,0L,2);
	cout<<ftell(fp)<<endl;
	fclose(fp);
	return 0;
}

