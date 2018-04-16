#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define SRC_PATH "./1.txt"
#define DEST_PATH "./2.txt"

int rfd,wfd;

void dojob(void)
{
	int cnt;
	char buff[1024];
	
	if(cnt = read(rfd,buff,1024)!=-1 )
		{
			cnt = write(wfd,buff,cnt);
		}

	pthread_exit(0);
}


int cpf(int num,char * src,char *dest)
{
	pthread_t ptid[num];
	int i;	

	for(i=0;i<num;i++)
		{
			pthread_create(&ptid[i],NULL,(void *)dojob,NULL);
			printf("pthread id = %d\n",ptid);
		}	
}


int main(int argc,char ** argv)
{
	int ret;

	rfd = open(SRC_PATH,O_RDONLY);
	if(rfd<=0) return -1;
	wfd = open(DEST_PATH,O_RDWR);
	if(wfd<0) return -1;
	//1. single thread copy file 
	cpf(2,SRC_PATH,DEST_PATH);
	while(1) sleep(1);
}
