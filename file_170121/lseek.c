#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h> 
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char **argv)
{
    typedef struct student{
       int num;
       char name[10];
       char sex[10];
       float score[3];
       float total;
    }STU;
	STU stu[3]={1003,"wang","男",34.0,76,87,197,1045,"yang","女",98,34,87,229,4547,"tiang","男",34.0,66,77,177};
	int fd;
	fd=open("student.txt",O_RDWR|O_CREAT,0666);
	if(-1==fd)
		perror("open");
	int fw,fr;
	fw=write(fd,stu,sizeof(stu));
	if(-1==fw)
	{	
		perror("write");
		return -1;
	}
	lseek(fd,0,SEEK_SET);
	STU buf[3];
	memset(buf,0,sizeof(buf));
    fr=read(fd,buf,sizeof(buf));
    if(-1==fr)
    {
        perror("write");
        return -1;
    }
	int i;
    for(i=0;i<3;i++)
    printf("%d %s %s %f %f %f %f\n",buf[i].num,buf[i].name,buf[i].sex,buf[i].score[0],buf[i].score[1],buf[i].score[2],buf[i].total);
	close(fd);
	return 0;
}
