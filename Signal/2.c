//描述：本文件主要描述从信号处理函数中跳出来跳出的场景，当前代码中，使用longjmp从信号处理函数中跳出，这中非
//      正常流程结束中断处理，会导致信号屏蔽字无法恢复，进而导致后续再怎么发信号，都无法再进入信号处理函数
//实际结果：结果与描述相符
//
//实验：现在增加和删除[001]的代码,在此尝试
//实验结果：中断处理函数可重入了，说明信号屏蔽字被解除了，这是因为sigsetjmp函数的第二个参数如果是1，那么代表
//          程序会额外保存一份当前状态下的信号屏蔽字，跳出时会强制刷新一次(貌似使用setjmp不会保存信号屏蔽字)
//
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>

sigjmp_buf sigenv;	//
jmp_buf env;

void Proc_SIGINT(int signo)
{
	printf("in handler(),[%d]\n",signo);
	//longjmp(env,1); //[001]
	siglongjmp(env,2); //[001]
}


int main(int argc,char ** argv)
{
	struct sigaction sa1,sa2;
	memset(&sa1,0x00,sizeof(struct sigaction));	
	memset(&sa2,0x00,sizeof(struct sigaction));

	sa1.sa_handler=Proc_SIGINT;

	sigaction(SIGINT,&sa1,&sa2);
	
	//setjmp(env); //[001]
	sigsetjmp(env,1); //[001] 使用sigsetjmp替换setjmp

	printf("xxxxx\n");
	while(1)
	{
		printf("in main()\n");
		sleep(3);
	}


}
