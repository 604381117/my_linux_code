#include"func.h"
int main(int argc,char **argv)
{
	if(argc!=2)
	{
	printf("error args\n");
	return -1;
	}
	FILE *fp;
	fp=popen(argv[1],"r");
	if(NULL==fp)
	{
	perror("fopen");
	return -1;
	}
	char buf[50]={0};
	fgets(buf,sizeof(buf),fp);
	puts(buf);
	pclose(fp);	
	return 0;
}
