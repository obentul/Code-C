#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>


struct sockaddr_in serv_addr;
socklen_t len;
int sock_fd=0;
pthread_t *t_id;
char *ip;
int port;
  
void dosth(void);
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
  

  bzero(&serv_addr,sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(port);
  inet_pton(AF_INET,ip,&serv_addr.sin_addr);

  sock_fd=socket(AF_INET,SOCK_STREAM,0);

  for(i=0;i<num;i++)
  {
    pthread_create(t_id,NULL,(void *)conn,NULL);
  }
  
  while(1) sleep(1);

}

void dosth(void)
{
  while(1) sleep(1);
}

void conn(void)
{
  int ret;
  ret=connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr));
  if(ret<0)
    {
      printf("unable to connect %s:%d\n",ip,port);
      exit(-1);
    }
  dosth();
}
