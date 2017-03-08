#include<stdlib.h>
#include<stdio.h>

void main()
{
	char ch;
	FILE *fp1=fopen("a.dat","wb");
	FILE *fp2;
	if(NULL==fp1)
	{
		printf("can not open this file\n");
		exit(0);
	}
	printf("please input a string:\n");
	ch=getchar();
	while(ch!='#')
	{
		fputc(ch,fp1);
		ch=getchar();
	}
	fflush(stdin);
	fclose(fp1);
	fp2=fopen("a.dat","rb");
	if(NULL==fp2)
	{
		printf("can not open this file!\n");
		exit(0);
	}
	while(!feof(fp2))	
	{
		ch=fgetc(fp2);
		putchar(ch);
	}
	putchar('\n');
	fflush(stdout);
	fclose(fp2);
}

