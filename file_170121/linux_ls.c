#include<dirent.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

void Getrwx(int* _rwx,char *str)
{
	int i;
	for(i=0;i<9;i++)
		if(*_rwx & 1<<i)
			if(i==0||i==3||i==6)
				str[9-i]='x';
			else if(i==1||i==4||i==7)
				str[9-i]='w';
			else if(i==2||i==5||i==8)
				str[9-i]='r';
}

void Getfiletype(int* type,char *str)
{
	if(S_ISDIR(*type))
		str[0]='d';
	else if(S_ISLNK(*type))
		str[0]='l';
	else if(S_ISREG(*type))
		str[0]='-';
	else if(S_ISCHR(*type))
		str[0]='c';
	else if(S_ISBLK(*type))
		str[0]='b';
	else if(S_ISFIFO(*type))
		str[0]='f';
	else if(S_ISSOCK(*type))
		str[0]='s';
}

void ls_display(char path[])
{
	struct stat buf;
	DIR* dir;
	if((dir=opendir(path))==NULL)
	{
		perror("opendir");
		return;
	}
	char str[10];
	struct dirent *p;
	int ret;
	struct tm *pT;
	while((p=readdir(dir))!=NULL)
	{
		memset(&buf,0,sizeof(buf));
		bzero(str,sizeof(str));
		strcpy(str,"----------");
		ret=stat(p->d_name,&buf);
		if(ret==-1)
		{
			perror("stat");
			return;
		}
		Getfiletype(&buf.st_mode,str);
		Getrwx(&buf.st_mode,str);
		pT=gmtime(&buf.st_mtime);	
		printf("%s %2d %3s %3s %5ld %4d-%02d-%02d %02d:%02d:%02d %-20s\n",\
			str,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,\
			getgrgid(buf.st_gid)->gr_name,buf.st_size,1900+pT->tm_year,\
			1+pT->tm_mon,pT->tm_mday,8+pT->tm_hour,pT->tm_min,pT->tm_sec,p->d_name);
	}		
}

int main(int argc,char **argv)
{
	if(argc==1)
		ls_display(getcwd(NULL,0));
	else if(2==argc)
		ls_display(argv[1]);
	else
	{
		printf("error args");
		return -1;
	}
	return 0;
}
