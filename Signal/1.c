//说明；1.通过sigprocmask函数从内核PCB中获取信号屏蔽字集，检查其中的SIGINT位是否被设置
//	2.程序运行循环输出SIGINT是否被设置，默认情况下，应该是不停输出"SIGINT is not SET"
//	3.我们修改了SIGINT信号的处理动作,并在其中在此阅读SIGINT的标志位
//	4.为了标记进入终端处理函数的次数，在中断处理函数中输出一个随机数
//期待结果：1.当我们向进程发送SIGINT信号时，期待输出"SIGIN is SET"
//	    2.当重复向进行发送SIGINT信号时，输出的随机数是不同的，因为进程可以多次进入信号处理函数
//输出结果：1.当我们向进程发送SIGINT信号时，依旧输出"SIGIN is not SET"，与预期不符
//	    2.当重复向进程发送SIGINT信号时，不会产生任何异常，程序还在原先的信号处理函数中执行，与预期不符
//解析：    1.由此可见，只有在信号未决期，信号的标志位才是1，一旦进入信号处理函数，标志位被移除
//          2.由此可见，当程序进入信号处理函数后，再次向其发送信号，内核默认是忽略的(也有可能在外面排队)
//
//
//补充实验：新增注释包含[001]的代码，如果在跳出终端处理函数后(日志输出中不再有随机数)，立即又再次进入终端处理函数
//          而且随机数改变了，那么就说明“内核管理了一个信号队列”
//实际结果：程序并没有立即再入，说明信号是“不排队的!!!”
//
//小结：一旦进入信号处理函数，那么后来的信号都被阻塞，而且不排队

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

sigset_t sigmask;       /*PCB中也有个这样数据类型，存放着所属进程的当前信号屏蔽字信息*/


void reset_SIGINT(int SIGNAL)	/*这里的入参，有系统自动填充，所以使用这个函数指针的时候，不需要指定入参(???)*/
{
	long lrandom=random();
	int i=0;
	printf("receiver[%d],i am [%ld],holding on...",SIGNAL,lrandom);
	while(1)
	{
		 if(sigismember(&sigmask,SIGINT))
			printf("SIGINT is SET  [%ld]  \n",lrandom);
		 else
			printf("SIGINT is not SET  [%ld]  \n",lrandom);
		 sleep(3);
		 if((i++)==5) break;   //[001]15秒后，跳出中断处理函数
	}
}


void print_sig(void)
{
	int tmp_errno;
	tmp_errno=errno;

	sigprocmask(0,NULL,&sigmask);	/*从PCB中拷贝出信号屏蔽字集*/
      
	while(1)
	{
		if(sigismember(&sigmask,SIGINT))
			printf("SIGINT is SET\n");
		else    
			printf("SIGINT is not SET\n");
		sleep(3);
	}

}


int main(int argc,char ** argv)
{
	struct sigaction action_SIGINT_NEW,action_SIGINT_OLD;
	memset(&action_SIGINT_NEW,0x00,sizeof(struct sigaction));	
	memset(&action_SIGINT_OLD,0x00,sizeof(struct sigaction));

	action_SIGINT_NEW.sa_handler = reset_SIGINT;

	sigaction(SIGINT,&action_SIGINT_NEW,&action_SIGINT_OLD);
	print_sig();
}
