#include<stdio.h>

int main(int argc,char **argv)
{
	if(argc!=2) 
	{
		perror("error args");
		return -1;
	}
	FILE* fp;
	fp=fopen(argv[1],"rb+");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	puts("hello",fp);
	fseek(fp,-5,SEEK_CUR);
	fputs("world",fp);
	fclose(fp);
	return 0;
}
