#include"func.h"
#define N 15

int main()
{
	int fd;
	fd=open("transfer_fd_to",O_RDWR|O_CREAT,0777);
	char buf[N]="wang dao-";
	char buf1[N]="belief dream";
	struct iovec iov[2];
	iov[0].iov_base=buf;
	iov[0].iov_len=9;
	iov[1].iov_base=buf1;
	iov[1].iov_len=12;
	writev(fd,iov,2);
	close(fd);
	return 0;
}
