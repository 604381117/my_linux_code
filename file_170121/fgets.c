#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	FILE *fp;
	char string[100];
	if((fp=fopen("file.txt","w"))==NULL)
	{
		perror("fopen");
		exit(0);
	}
	while(strlen(gets(string))>0)
	{
		fputs(string,fp);
		fputs("\n",fp);
	}
	fclose(fp);
	if((fp=fopen("file.txt","r"))==NULL)
	{
		perror("fopen");
		exit(0);
	}
	while(fgets(string,10,fp)!=NULL)
		fputs(string,stdout); //puts(string)
	fclose(fp);
}

