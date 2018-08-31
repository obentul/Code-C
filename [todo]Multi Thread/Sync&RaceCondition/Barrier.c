/* 说明；屏障的作用相当于创建一个计时器，为这个计数器设置一个数值，每个线程可以通过pthread_barrier_wait来为这个计数器+1，然后阻塞等待，当计数器的值达到之前设置的值时，所有
 * 线程一并退出阻塞状态(可以用这个来模拟瞬间并发)。
 *
 *
 *
 * */

#include "mythread.h"

#define DEF_NUM 20


pthread_barrier_t ba;

void * func(void *args)
{
	struct thread_stu *tmp;
	tmp = (struct thread_stu *)args;
	printf("[WORKID = %d]\n",tmp->thread_workid);
	pthread_barrier_wait(&ba);
}

void do_job()
{
	printf("over\n");
}

int main(int argc,char **argv)
{
	int i;
	struct thread_stu st[DEF_NUM];

	pthread_barrier_init(&ba,NULL,DEF_NUM+1);  //这里有个小技巧，让计数器是所有线程数的+1，这样可以让主线程来完成最后一个pthread_barrier_wait，从而让主线程掌握程序的节奏

	for(i=0;i<DEF_NUM;i++)
	{
		st[i].thread_tid=0;
		st[i].thread_workid=i;
		st[i].thread_ret=NULL;
		st[i].thread_desc=NULL;
		st[i].args=&st[i];
		st[i].thread_func=func;

		pthread_create(&st[i].thread_tid,NULL,st[i].thread_func,st[i].args);
	}

	sleep(1);//sleep以等待子线程先结束
	pthread_barrier_wait(&ba); //  这里是存在风险的，子线程可能执行的比较慢，而导致主线程提前pthread_barrier_wait(&ba)，这里只是做DEMO，不去详细研究
	
	printf("main thread's turn\n");

	do_job();
}





