#include "func.h"
//打开源文件
//创造目标文件并制造文件空洞
//mmap两个文件到内存中，返回两个地址
filemaps creatFile()
{
	int fd_tar;
	if((fd_tar = open(FILENAME, O_RDWR)) == -1)
	{
		perror("open");
		exit(0);
	}
	off_t filesize = lseek(fd_tar, 0, SEEK_END);
	lseek(fd_tar, 0, SEEK_SET);

	
	unsigned long n = 0;
	for(int i = 0;;i++){
		if((1<<i) > filesize){
			n = 1<<i;
			break;
		}
	}
	char *source = (char *)mmap(NULL, n, PROT_READ, MAP_SHARED, fd_tar, 0);

	int fd_new;
	char newfilename[20] = {0};
	sprintf(newfilename, "copy_%s", FILENAME);
	//注意，这个地方打开方式一定要读写，如果不加读属性，就无法把文件映射到内存，导致mmap失败。
	if((fd_new = open(newfilename, O_RDWR |O_CREAT, 0666)) == -1){
		perror("open");
		exit(0);
	}
	ftruncate(fd_new, filesize);
	char *target = (char *)mmap(NULL, n, PROT_WRITE, MAP_SHARED, fd_new, 0);
	
	filemaps ret;
	ret.source = source;
	ret.target = target;
	printf("%p %p\n", source, target);
	ret.aversize = filesize / 10;
	ret.filesize = filesize;
	return ret;
}
//线程函数，用memcpy实现映射内存的写操作
void* threadFunc(void *pmtemp)
{
	filemaps *pmtem = (filemaps *)pmtemp;
	int len = pmtem->aversize;
	if(len == 9)
		len = pmtem ->filesize - 9 * pmtem ->aversize;
//	printf("%d\n",pmtem->thid);
//	printf("%ld %ld\n", pmtem->aversize * pmtem->thid, len);
	memcpy(pmtem ->target + pmtem->aversize * pmtem->thid,
			pmtem->source + pmtem->aversize * pmtem->thid,
				len);
}
//分10个线程，各自拷贝十分之一
void quickCopy(filemaps *const pmaps)
{
	pthread_t thid[10];	
	filemaps mtemp[10];

	for(int i = 0; i<10; i++){
		memcpy(&mtemp[i], pmaps, sizeof(filemaps));
		mtemp[i].thid = i;
		if(i == 9)
			mtemp[i].aversize = mtemp[i].filesize % 10;
		pthread_create(&thid[i], NULL, threadFunc, &mtemp[i]);
	}
	
	for(int i = 0; i<10; i++){
		pthread_join(thid[i], NULL);
	}
}
//释放资源
void freeSource(filemaps *tar)
{
	munmap(tar->source, tar->filesize);
	munmap(tar->target, tar->filesize);
}
int main()
{
	filemaps mymaps;
	mymaps = creatFile();
//	return 0;
	quickCopy(&mymaps);
	freeSource(&mymaps);
	return 0;
}
