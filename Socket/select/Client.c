#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>

struct sockaddr_in serv_addr;
socklen_t len;
pthread_t *t_id;
char *ip;
int port;
  
void dosth(int);
void conn(void);

int main(int argc,char ** argv)
{
  int i;
  int num;

  if(argc!=4)
  {
    printf("wrong num of arg,need to be 4,now is %d\n",argc);
    exit(-1);
  }
  ip=argv[1];
  port=atoi(argv[2]);
  num=atoi(argv[3]);
  t_id = malloc(sizeof(pthread_t)*num);
  printf("connet to %s:%d,with %d pthreads\n",ip,port,num);
  

  memset(&serv_addr,0x00,sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(port);
  serv_addr.sin_addr.s_addr = inet_addr(ip);


  for(i=0;i<num;i++)
  {
    pthread_create(t_id,NULL,(void *)conn,NULL);
  }
  
  while(1) sleep(1);

}

void dosth(int sock_fd)
{
  char buff;
  //此函数在线程栈里，虽然代码是公用的，但是每个线程都有自己的一份此函数的上下文
  printf("tid = %ld\n",pthread_self());

  read(0,&buff,1);
  if(buff=='g')
	write(sock_fd,"xxxx\n",6);

  printf("\n");	//手工冲洗缓冲区，让之前输入的g可以被读入，不然程序会卡在那卡着，当然也可以fflush，printf简单粗暴
	
  while(1) sleep(1);
}

void conn(void)
{
  int ret,sock_fd;
  sock_fd=socket(AF_INET,SOCK_STREAM,0);	//考虑到线程共享全局变量，所以sock_fd应该定义在线程里面
  ret=connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
  if(ret<0)
    {
      perror("connect error:");
      printf("unable to connect %s:%d\n",ip,port);
      exit(-1);
    }
  dosth(sock_fd);
}
