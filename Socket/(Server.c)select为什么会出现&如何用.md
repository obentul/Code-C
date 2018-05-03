# 承上《accept的用法-1.md》

# 使用accept监控多个文件描述符的时候，有如下问题：  
  -- 1.代码量大，多一个socket，就多一个accept；  
  -- 2.如果某个fd是阻塞的，那么后面的fd都不可被监控；  
  -- 3.没办法设置一个超时时间，用来表示监控某个描述符多久可以跳出阻塞；  
  -- 4.总的来说，对于每一个socket，都需要调用accept来判断是否可读，这样就很低效；
  -- 5.理想的情况是，“accpet每次都是成功的，而不是用来做判断”，这个思路很重要
  
# 基于上面的第5点，那么就需要一个函数来为accept服务，为它提供可用的socket描述符，select/poll/epoll就是用来干这个事的  

# select函数可以用来轮训文件描述符，并返回有多少个文件描述符已经准备好（可读/可写/异常），后面我们只要去挨个accept这些  
  描述符即可。  
  下面为使用select轮训两个socket的例子：
 
```
//select阻塞  +  描述符不阻塞
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>

#define PORT 6666
#define PORT_1 7777


int main(int argc,char **argv)
{
        struct sockaddr_in addr,addr1,caddr,caddr1;
        int lfd,lfd1,cfd,cfd1,i;
        socklen_t clien,clien1;

        struct timeval timeout;
        fd_set readfds;

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

        fcntl(lfd1,F_SETFL,fcntl(lfd1,F_GETFL)|O_NONBLOCK);  //描述符不阻塞  
        fcntl(lfd,F_SETFL,fcntl(lfd,F_GETFL)|O_NONBLOCK);    //描述符不阻塞  
        
        while(1){
                clien = sizeof(caddr);
                clien1 = sizeof(caddr1);
                
                FD_ZERO(&readfds);
                FD_SET(lfd,&readfds);
                FD_SET(lfd1,&readfds);
                
                i=select(lfd+1,&readfds,NULL,NULL,NULL);  //select阻塞

                printf("there %d fds is ready to be dealed\n");

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
```
结果：  
阻塞在select的地方  
可见，select的计时阻塞和描述符是否阻塞是没有关系的
```

```
//select不阻塞  +  描述符阻塞
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>

#define PORT 6666
#define PORT_1 7777


int main(int argc,char **argv)
{
        struct sockaddr_in addr,addr1,caddr,caddr1;
        int lfd,lfd1,cfd,cfd1,i;
        socklen_t clien,clien1;

        struct timeval timeout;
        fd_set readfds;

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
                
                FD_ZERO(&readfds);
                FD_SET(lfd,&readfds);
                FD_SET(lfd1,&readfds);
                
                i=select(lfd+1,&readfds,NULL,NULL,&timeout); //select不阻塞
                
                printf("there %d fds is ready to be dealed\n");

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
```
结果：阻塞在there %d fds is ready to be dealed
可见，select不阻塞并不会修改相应文件描述符的阻塞标志位
```

# 结论：select的超时时间参数，可设置为阻塞（NULL）、非阻塞（0）和任意时间，这个参数仅仅影响select的状态，并不影响文件描述符
  阻塞标志位，select的阻塞与否 和 文件描述符的阻塞与否 是完全相互独立的。

