#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	DIR *dir;
	dir=opendir(argv[1]);
	if(NULL==dir)
	{
		perror("opendir");
		return -1;
	}
	struct dirent *p;
	off_t pos;
	while((p=readdir(dir))!=NULL)
	{
		if(!strcmp(p->d_name,"opendir1.c"))
		{
			pos=telldir(dir);//读到argv[1]文件后，记录当时的位置
			if(-1==pos)
			{
				perror("dir");
				return -1;
			}
		}
		printf("inode=%ld,len=%d,type=%d,%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);	
	}
#if 0
	rewinddir(dir);//回到目录开头
	p=readdir(dir);
	printf("inode=%ld,len=%d,type=%d,%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
#endif
	seekdir(dir,pos);
	p=readdir(dir);
	printf("inode=%ld,len=%d,type=%d,%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
	closedir(dir);
	return 0;
}
