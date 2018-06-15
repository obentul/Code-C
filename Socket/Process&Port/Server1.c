#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#define PORT 6666

int main(int argc,char **argv)
{
        struct sockaddr_in addr,caddr;
        int lfd,cfd;
        socklen_t clien;
	fd_set rfds;
	struct timeval tv;

	int n;
	int retval=0;
	int retvalcnt=0;

	FD_ZERO(&rfds);

	//初始时间
	tv.tv_sec=5;
        tv.tv_usec=0;

        memset(&caddr,0x00,sizeof(struct sockaddr_in));
        memset(&addr,0x00,sizeof(struct sockaddr_in));

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(PORT);

        lfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        bind(lfd,(struct sockaddr_in *)&addr,sizeof(addr));
        listen(lfd,20);	//最多有20*1.4个连接

goon:
	clien = sizeof(caddr);
		cfd=accept(lfd,(struct sockaddr_in*)&caddr,&clien); //这里没有对lfd做非阻塞设置，故此处阻塞等待
	int pid=0;
	pid = fork();
	if(pid>0)
		{
			printf("father get the request\n");
			goto goon;
		}	
	if(pid==0)
		{	
		goon1:
			accept(lfd,(struct sockaddr_in*)&caddr,&clien);//子进程在此监听
			
			
	
			printf("child get the 2nd request\n");
			goto goon1;
		}



	printf("连接数+1,当前%d,cfd=%d\n",n,cfd);
		FD_SET(cfd,&rfds);				    //把已连接套接字塞入可读轮询列表
	
int j=0;
        while(1){
		//每次都要重新设置下时间，因为select一旦有一次超时返回，那么其超时剩余时间就是0，那么tv的值就会被设置成0，接着select就相当于
		//没有阻塞等待，伴随而来的就是while(1)循环中的无限select，问题的关键点就在这里，这也是为什么会吃CPU的原因。
		//man手册中有明确写出了，而且建议使用pselect，pselect既线程安全，又不会改变tv值
		tv.tv_sec=5;
		tv.tv_usec=0;
		//轮询刚才那5个已连接socket，5s的阻塞等待时间
		retval = select(cfd+1,&rfds,NULL,NULL,&tv);
	        if (retval == -1)
                   perror("select()");
	        else if (retval)
                {
			printf("Data is available now.\n");
			//当5个连接都可读以后，跳出循环，程序结束
			retvalcnt=retvalcnt+retval;
			if(retvalcnt==5) break;
		}
                else
                printf("No data within five seconds.\n");
        }
	printf("xxx\n");
}


/* 使用方法：gcc Server1.c -o s
 * 	     gcc Client.c -o c
 * 	      ./s
 * 	      ./c 127.0.0.1 6666 5 &    （一次创建五个线程，都去连接s）
 *
 *	     top -p (s的pid)
 *	     watch -n 0.1 ‘netstat -an|grep 6666’
 * */

/* 结果：1.当创建完5个c后，s端每5s输出一个“No data within five seconds.”
 * 	2.控制5个c依次向socket中写数据后，s依次输出5个“Data is available now.”，然后程序结束
 *      3.  2中的控制c就是在c的等待输入行输入 字符  g
 *
 *
 * */








