//描述：通过sigpending函数查询当前进程下，所有被阻塞的信号，此函数可以用来检查某个信号当前是否处于阻塞，也可以依次性获取N多个处于阻塞态的信号集
//	
//结果
//
//
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char ** argv)
{
	sigset_t st_new,st_old,st_pend;
	
	sigemptyset(&st_new); //初始化
	sigaddset(&st_new,SIGUSR1); //组装
	
	sigprocmask(0,NULL,&st_old); //获取本进程当前的屏蔽字
	prn_mask();
	
	sigprocmask(SIG_BLOCK,&st_new,&st_old); //合并组装屏蔽字和旧屏蔽字
	prn_mask();
	
	sigpending(&st_pend);	//获取等待信号集，这里的sigset结构仅仅用作存放信号掩码，不用做用作屏蔽字
	if(sigismember(&st_pend,SIGUSR1)) printf("SIGUSR1 is pending\n");
	else printf("SIGUSR1 is NOT pending\n");
	
	raise(SIGUSR1);

	sigpending(&st_pend);
        if(sigismember(&st_pend,SIGUSR1)) printf("SIGUSR1 is pending\n");
        else printf("SIGUSR1 is NOT pending\n");

	
	while(1) sleep(1);


}
