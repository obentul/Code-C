# 以下程序不会有任何输出，因为程序阻塞在accept那里了(实际上accpet监听的socket描述符是阻塞的)
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 6666

int main(int argc,char **argv)
{
        struct sockaddr_in addr,caddr;
        int lfd,cfd;
        socklen_t clien;

        memset(&caddr,0x00,sizeof(struct sockaddr_in));
        memset(&addr,0x00,sizeof(struct sockaddr_in));

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(PORT);

        lfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        bind(lfd,(struct sockaddr_in *)&addr,sizeof(addr));
        listen(lfd,20);


        while(1){
                clien = sizeof(caddr);
                cfd=accept(lfd,(struct sockaddr_in*)&caddr,&clien);

                printf("hello\n");
                sleep(1);
        }


}
```

# 以下程序会有正常输出，因为把accept监听的socket描述符转换成非阻塞了
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#define PORT 6666

int main(int argc,char **argv)
{
        struct sockaddr_in addr,caddr;
        int lfd,cfd;
        socklen_t clien;

        memset(&caddr,0x00,sizeof(struct sockaddr_in));
        memset(&addr,0x00,sizeof(struct sockaddr_in));

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(PORT);

        lfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        bind(lfd,(struct sockaddr_in *)&addr,sizeof(addr));
        listen(lfd,20);

        fcntl(lfd,F_SETFL,fcntl(lfd,F_GETFL)|O_NONBLOCK);

        while(1){
                clien = sizeof(caddr);
                cfd=accept(lfd,(struct sockaddr_in*)&caddr,&clien);
                printf("cfd = %d\n",cfd);
                printf("hello\n");
                sleep(1);
        }
}
```
输出结果： 
```
cfd = -1   
hello   
cfd = -1   
hello   
cfd = -1   
hello   
```

# 小结：accept本身不是一个阻塞函数，所以讨论accept的阻塞与否本身就是错误的

# 那么，我现在想监听两个端口，有如下程序：
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#define PORT 6666
#define PORT_1 7777


int main(int argc,char **argv)
{
        struct sockaddr_in addr,addr1,caddr,caddr1;
        int lfd,lfd1,cfd,cfd1;
        socklen_t clien,clien1;

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

        fcntl(lfd1,F_SETFL,fcntl(lfd1,F_GETFL)|O_NONBLOCK);
        fcntl(lfd,F_SETFL,fcntl(lfd,F_GETFL)|O_NONBLOCK);

        while(1){
                clien = sizeof(caddr);
                clien1 = sizeof(caddr1);

                cfd1=accept(lfd1,(struct sockaddr_in*)&caddr1,&clien1);
                cfd=accept(lfd,(struct sockaddr_in*)&caddr,&clien);

                printf("cfd1 = %d\n",cfd1);
                printf("cfd = %d\n",cfd);
                printf("hello\n");
                sleep(1);
        }
}
```
输出结果：
```
cfd1 = -1
cfd = -1
hello
cfd1 = -1
cfd = -1
hello
```

# 小结：一个程序可以同时监控多个socket文件描述符，但是在处理cfd的时候，需要"挨个判断返回值"



