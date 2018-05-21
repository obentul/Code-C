#include "Server1.h"
#include <stdio.h>

//global
struct server_info server1;
struct client_info *client1;
int lis_sock_fd;

int init_sys(void);
int init_socket(void);
int start_accept(int n);
int start_epoll(int n);

int main(int argc,char ** argv)
{
	//0.init system sources(signal handler & others)
	init_sys();
	//1.init socket
	init_socket();
	//2.create a accept thread
	start_accept(server1.accept_thread_def);
	//3.create epoll thread
	start_epoll(sercer1.epoll_thread_def);
	//4.rcycle thread
	//5.clean,if break out from 4
}

/* 0 -- success
 * -1 -- fail
 * */
int init_sys(void)
{

}

int init_socket(void)
{
	printf("init_socket start\n");
	//init server1
	memset(&server1,0x00,sizeof(struct server_info));
	server1.ip = IP_SERV;
	server1.port = PORT_SERV;
	server1.domain_anme = DOMAIN_SERV;
	server1.desc = DESC_SERV;
	server1.link_max = LINK_MAX;


        //make addr
        struct sockaddr_in addr,caddr;
	memset(&caddr,0x00,sizeof(struct sockaddr_in));
	memset(&addr,0x00,sizeof(struct sockaddr_in));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(server1.ip);
	addr.sin_port=htons(server1.port);

	printf("init_socket #1\n");

	//socket()
	lis_sock_fd = socket(AF_INET,SOCK_STREAM,IPROTO_TCP);
	
	printf("init_socket #2\n");

        //bind()
	bind(lis_sock_fd,(struct sockaddr_in *)&addr,sizeof(addr));

	printf("init_socket #3\n");

        //listen()
        listen(server1.link_max);

	printf("init_socket done\n");
}


int start_accept(int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		pthread_create();
	}
}

void do_accept(void)
{
	//accpet
	do(accept)
	{
		printf("new connection , put into ready tobe read queue\n");
		//try to lock queue
		//put into queue
		//unclock queue
	}while(1);
}

int start_epoll(int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		pthread_create(,(void *)do_epoll_read,);
	}
	for(i=0;i<m;i++)
	{
		pthread_create(,(void *)do_epoll_write,);
	}
}


/* 轮询所有已连接套接字，找出其中可读的，父进程继续轮询，子进程调用mq_sender处理可读已连接套接字列表
 *
 *
 * */
void do_epoll_read(void)
{
	int pid;

	do(epoll)
	{
		printf("connection readable , give them to mq_senderS\n");
		pid = fork();
		if(pid > 0)
		{
			continue;
		}
		if(pid = 0)
		{
			mq_writer();
		}
	}while(1);
}

/* 检查所有已连接套接字是否在黑名单中，读取
 *
 * */
void mq_writer(void)
{
	//blacklist check

	//put it into message queue;应该是多线程写消息队列
	
}

void do_epoll_write(void)
{

}

void mq_reader(void)
{
	//read message from queue;
	
	
}



