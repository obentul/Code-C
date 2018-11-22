#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 6666



int main(int argc,char ** argv)
{

	int listen_fd,conn_fd;
	struct sockaddr_in sev_addr,cli_addr;
	int iRet;
	int cli_len;
	int pid;
	char buff[1024];
	int nbytes;
	
	memset(&sev_addr,0x00,sizeof(sev_addr));	
	memset(&cli_addr,0x00,sizeof(cli_addr));
	memset(buff,0x00,sizeof(buff));	

	sev_addr.sin_family = AF_INET;
	sev_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sev_addr.sin_port = htons(6666);

	listen_fd = socket(AF_INET,SOCK_STREAM,0);
	iRet	  = bind(listen_fd,(struct sock_addr *)&sev_addr,sizeof(sev_addr));
	iRet	  = listen(listen_fd,20);
	
	again:
	conn_fd   = accept(listen_fd,(struct sock_addr *)&cli_addr,&cli_len);
	
	if(conn_fd > 0)
	{
		pid = fork();
		if(pid==0)
			{
				pid = fork();
				if(pid!=0)	exit(0);
				do{
				   nbytes = read(conn_fd,buff,sizeof(buff));
				   printf("recv:%s\n",buff);
				   write(conn_fd,buff,strlen(buff));
				}while(nbytes!=0&&nbytes!=-1);
				exit(0);
			}
		if(pid>0)
			{
				goto again;
			}
		if(pid<0)
			{
				printf("fork error\n");
				exit(-1);
			}
	}

}
