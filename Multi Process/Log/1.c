#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc,char ** argv)
{

	char tmp[10]={0};
	int n;
	

	int fd = open("./1.log",O_RDONLY|O_APPEND);
	if(fd<0)
	perror("open fd error");

	char pathname[100];
	memset(pathname,0x00,sizeof(pathname));
	sprintf(pathname,"%d.cpy",getpid());
	int fd_1 = open(pathname,O_CREAT|O_RDWR);
	if(fd_1<0)
	perror("open fd_1 error:");
	

	while((n = read(fd,tmp,10))!=0)
	{
		if(n<0)
		perror("read error:");
		write(fd_1,tmp,n);
		bzero(tmp,10);
		sleep(1);
	}
}
