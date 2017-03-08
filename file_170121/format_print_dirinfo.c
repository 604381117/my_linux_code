#include"func.h"
void find_file(char *path, char name[])
{
	DIR* dir;
	if(NULL==(dir=opendir(path)))	
	{
		perror("opendir");
		return;
	}
	struct dirent *p;
	char buf[100]={0};
	while((p=readdir(dir))!=NULL)
	{
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
			continue;
		if(!strcmp(p->d_name,name))
			printf("%s%c%s\n",path,'/',name);
		if(p->d_type==4)
		{	
			sprintf(buf,"%s%c%s",path,'/',p->d_name);
			find_file(buf,name);
		}	
	}
	closedir(dir);
}

int main(int argc,char **argv)
{
	if(3!=argc)
	{
	printf("error args\n");
	return -1;
	}
	char buf[100]={0};
	chdir(argv[1]);
	strcpy(buf,getcwd(NULL,0));
	chdir(argv[1]);
	find_file(buf,argv[2]);
	return 0;
}
