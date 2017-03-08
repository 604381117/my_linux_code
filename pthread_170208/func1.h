#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/mman.h>

#define FILENAME "1.mp4"

typedef struct filemaps
{
	char *source;
	char *target;
	long aversize;
	long filesize;
	int thid;	
}filemaps;
