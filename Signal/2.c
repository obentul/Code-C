#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define BLOCKED	SIGCHLD|SIGTTIN	 //当进入信号处理函数时，这些信号将被屏蔽(1.触发信号会默认被屏蔽，除非在flag字段做了说明；2.非可屏蔽信号不能被屏蔽)
				 //因此，默认情况下，信号是排队依次进入信号处理函数的，不能并
#define BEHAVIOR 

struct sigaction stu_CTL;

void CTLC_DL(int signo, siginfo_t * info, void * v)
{
	


}

int main(int argc,char ** argv)
{
	memset(stuCTL,0x00,sizeof(struct sigaction));
	stuCTL.sa_sigaction=CTLC_DL;
	sa_mask= ;
	sa_flags= ;

	sigaction(SIGINT,);

	printf("background process,pid=%d\n",getpid());
}
