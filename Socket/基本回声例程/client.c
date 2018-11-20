#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc,char ** argv)
{
	int conn_fd;
	int nbytes;
	char buff[1024];
	int iRet;	
	
	struct sockaddr_in cli_addr;

	memset(buff,0x00,sizeof(buff));
	memset(&cli_addr,0x00,sizeof(cli_addr));

	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	cli_addr.sin_port = htons(6666);

	conn_fd = socket(AF_INET,SOCK_STREAM,0);
	iRet	= connect(conn_fd,(struct sockaddr *)&cli_addr,sizeof(cli_addr));
		if(iRet!=0)
			{
				perror("connect error\n");
				exit(-1);
			}
	while(1)
	{
		fgets(buff,1024,stdin);
		write(conn_fd,buff,strlen(buff));
		printf("send:%s\n",buff);
	}


}
