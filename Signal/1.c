//说明；1.通过sigprocmask函数从内核PCB中获取信号屏蔽字集，检查其中的SIGINT位是否被设置
//	2.程序运行循环输出SIGINT是否被设置，默认情况下，应该是不停输出"SIGINT is not SET"
//	3.我们修改了SIGINT信号的处理动作,并在其中在此检查SIGINT是否在信号屏蔽字里
//	4.为了标记进入终端处理函数的次数，在中断处理函数中输出一个随机数
//期待结果：1.当我们向进程发送SIGINT信号时，期待输出"SIGIN is SET"
//	    2.当重复向进行发送SIGINT信号时，输出的随机数是不同的，因为进程可以多次进入信号处理函数
//输出结果：1.当我们向进程发送SIGINT信号时，确实输出“SIGIN is SET”，与预期相符
//	    2.当重复向进程发送SIGINT信号时，不会立即中断当前中断处理，而是有一个排队的机制，即在第一个中断处理结束后，
//	      顺序进入下一个中断处理，”但是“，貌似队列是有长度的，或者说是由定时器限制的，并不是发多少就依次进入多少次
//	      这里需要详细研究下，试验中，发了3次，只进入两次，发了10次只进入三次。
//解析：    1.一旦进入信号处理函数，那么此信号将被塞入信号屏蔽字中，后续再来的信号将被阻塞
//          2.由此可见，当程序进入信号处理函数后，再次向其发送信号，信号会在”一定程度上“排队
//
//
//补充实验：新增注释包含[001]的代码，如果在跳出终端处理函数后(日志输出中不再有随机数)，立即又再次进入终端处理函数
//          而且随机数改变了，那么就说明“内核管理了一个信号队列”
//实际结果：程序有再次进入，但是次数不确定，这里需要研究研究
//
//小结：1.一旦进入信号处理函数，那么后来的信号都被阻塞,信号屏蔽字会被设置，一直到出信号处理函数，屏蔽字才会被重新复位
//	2.同样的信号会进行一定程度上的排队，具体的机制需要详细研究

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
		 sigprocmask(0,NULL,&sigmask);   /*从PCB中拷贝出信号屏蔽字集*/		 
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

	while(1)
	{
		sigprocmask(0,NULL,&sigmask);   /*从PCB中拷贝出信号屏蔽字集*/
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
