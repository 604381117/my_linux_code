#include<stdlib.h>
#include<stdio.h>

void main()
{
	char ch;
	FILE *fp1=fopen("a.dat","wb");
	if(NULL==fp1)
	{
		printf("can not open this file\n");
		exit(0);
	}
	printf("please input a string:\n");
	ch=fgetc(stdin);
	while(ch!='#')
	{
		fputc(ch,fp1);
		ch=fgetc(stdin);
	}
	fflush(stdin);
	fclose(fp1);
	fp1=fopen("a.dat","rb");
	if(NULL==fp1)
	{
		printf("can not open this file!\n");
		exit(0);
	}
	while(!feof(fp1))	
	{
		ch=fgetc(fp1);
		fputc(ch,stdout);
	}
	fputc('\n',stdout);
	fflush(stdout);
	fclose(fp1);
}

