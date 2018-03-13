# 承上《accept的用法-1.md》 《select为什么会出现&如何用.md》

# select解决了“accept准确率”的问题，但是有个新的问题，那就是返回值表示有多少个准备好了，并不罗列多少个可读，多少个可写等信息，更   
  不谈罗列哪些可读，哪些可写；需要使用FD_ISSET来判断期待的描述符是否在集合里被置位了，那么这和我while(1)轮训判断accept的返回值   
  的差别并不是很大（无阻塞socket描述符的情况），“因为我还是要去判断到底哪些可读”，select只是多了一个轮训时间 以及 告诉我有多少个  
  可读。
  
# poll  
  poll和select的内部机理是一样的，就是在使用的时候不一样，可以把poll理解为select的“好用版本”
  比如，监听两个描述符，使用poll的代码如下：
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>

#define PORT 6666
#define PORT_1 7777

#define MAX_SCAN_FDSET   10  //定义poll 监听的文件描述符集合的大小(理论上可以无限大)
#define POLL_WAIT_TIMEOUT   10*1000    //poll的超时时间，单位是毫秒，0表示无阻塞，-1表示一直阻塞

int main(int argc,char **argv)
{
        struct sockaddr_in addr,addr1,caddr,caddr1;
        int lfd,lfd1,cfd,cfd1,i;
        socklen_t clien,clien1;

        struct timeval timeout;
		
		struct pollfd scan_fdset[MAX_SCAN_FDSET];

        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        memset(&caddr,0x00,sizeof(struct sockaddr_in));
        memset(&caddr1,0x00,sizeof(struct sockaddr_in));
        memset(&addr,0x00,sizeof(struct sockaddr_in));
        memset(&addr1,0x00,sizeof(struct sockaddr_in));

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(PORT);
        addr1.sin_family = AF_INET;
        addr1.sin_addr.s_addr = htonl(INADDR_ANY);
        addr1.sin_port = htons(PORT_1);

        lfd1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        lfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        bind(lfd,(struct sockaddr_in *)&addr,sizeof(addr));
        bind(lfd1,(struct sockaddr_in *)&addr,sizeof(addr));
        listen(lfd,20);
        listen(lfd1,20);

        while(1){
                clien = sizeof(caddr);
                clien1 = sizeof(caddr1);
                
				scan_fdset[0].fd=cfd;
				scan_fdset[0].events = POLLIN|POLLOUT;  //cfd可读可写
				scan_fdset[1].fd=cfd1;
				scan_fdset[1].events = POLLIN|POLLOUT;  //cfd1可读可写
				
				i=poll(&scan_fdset,2,3000)	//目前设置了2个，开始轮训，没3s返回一次轮训结果

                printf("there %d fds is ready to be dealed\n",i);

                cfd1=accept(lfd1,(struct sockaddr_in*)&caddr1,&clien1);
                cfd=accept(lfd,(struct sockaddr_in*)&caddr,&clien);

                printf("there %d fds is ready to be dealed\n");
                printf("cfd1 = %d\n",cfd1);
                printf("cfd = %d\n",cfd);
                printf("hello\n");
                sleep(1);
        }
}
```
  
# epoll
  poll解决了select能监听个数的限制，扩展到了无限数目，但是用起来还是和select一样，还是要在函数返回后对相应的描述符状态进行判断  
  select中使用FD_ISSET判断，poll中使用fd[n].revents的值判断。  
  
  
  
  
