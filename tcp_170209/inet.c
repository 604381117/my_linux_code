#incldue"func.h"

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("error args")
		return -1;
	}
	struct in_addr add;
	memset(&add,0,sizeof(add));
	int ret=inet_aton(argv[1],&add);
	if(0==ret)
	{
		perror("inet_aton");
		return -1;
	}
	printf("add=%x\n",add.s_addr);
	printf("ip=%s\n",inet_noa(add));
	unsigned long add1;
	add1=iinet_addr(argv[1]);
	printf("add1=%x\n",add1);
	return 0;
}
