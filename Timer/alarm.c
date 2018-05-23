//功能描述：在5s内轮询产生的随机数(1s生产一个随机数)，判断随机数是不是100的整数倍，如果是，则输出定时器剩余时间，如果不是，继续

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <setjmp.h>

enum{
	TIMER_HANDLER=1,	//来自中断处理函数跳转点
};

#define SAVE_SIGMASK 1

long lrandom;	//随机数
int remain;	//剩余时间

void endup(void);
void do_clean(void);
void timer_handler(void);
jmp_buf sv_p1;


int main(int argc,char ** argv)
{
	int interval=5;//多久中断超时一次
	int iRet;	
	signal(SIGALRM,(void *)timer_handler);

	//setjmp(sv_p1); //不使用
	iRet = sigsetjmp(sv_p1,SAVE_SIGMASK);
	if(iRet == TIMER_HANDLER)
	{
		//从中断处理函数跳过来的
		printf("jump from void timer_handler(void)\n");
	}
	else
	{
		//从其他地方跳过来的
	}
	
	alarm(interval);//开始计时
	while(1)
	{
		sleep(1);
		lrandom=random();
		int yushu;
		yushu=lrandom%100;//求余数
		printf("yushu = [%ld],lrandom = [%ld]\n",yushu,lrandom);
		if(yushu==0)
		{
			//整除了
			remain = alarm(0);//cancle counter,return remain seconds
			printf("got a number which can be divided by 100 , %d seconds remaining,num is [%ld]\n",remain,lrandom);
			alarm(interval);	//重置定时器
		}
	}
}

void timer_handler(void)
{
	printf("time out\n");
	//1.end of process
	//endup();
	//2.jump to somewhere,goto 只能在当前栈内跳转，栈外跳转使用longjmp系列，
	//这里使用siglongjmp和sigsetjmp，因为使用longjmp和setjmp在入中断处理函数后，
	//会自动把中断掩码清0，这样可屏蔽中断就全都被关闭了，下次再满足中断条件也不会入中断了

	printf("goto save point 1\n");
	//longjmp(sv_p1,TIMER_HANDLER)  //不使用
	siglongjmp(sv_p1,TIMER_HANDLER);//TIMER_HANDLER为返回值，这个值作为sigsetjmp的返回值，用来判断跳转点
}

void endup(void)
{
	do_clean();
	exit(-1);
}

void do_clean(void)
{

}
