/* 说明：1.条件变量可以理解为信号
*       2.当某个条件(自定义)产生后，内核会自动通知条件变量注册列表中的所有线程(或者随即某个线程)
*       3.条件变量API中互斥量参数的作用：保护条件变量(可以理解条件变量为公共资源)
*       4.传递给API的互斥量必须是被锁住的
*  举个例子：1）有两个线程A和B，如果A执行到某一步，再想往下执行需要满足全局变量VA=1，比如while(VA!=1);这样，那么这就造成了轮询，有因为VA是全局的，肯定
            还有竞争，那么全部代码应该是
                                      while(1){
                                      pthread_mutex_lock(&mutex_VA); 
                                      if(VA==1) {dosomething();break;}
                                      else donothing();
*                                     pthread_mutex_unlock(&mutex_VA);
                                      }
            这样还是比较低效的，首先需要判断资源是不是可用，其次需要看资源的值是否满足，如果满足还好，如果不满足就要进while(1)循环，如果资源一直可读，
            那么就是忙等状态。此时，只有B线程对mutex_VA加锁，然后让VA==1,下次轮询时，A线程才会进入dosomething。
            2）那么如果我们使用条件变量，只需要通过调用pthread_cond_wait把本线程挂到条件变量的轮询列表中，阻塞等待即可。但是！！！需要B线程调用
            pthreadc_cond_signal/pthread_cond_broadcast来手动发出信号(在发之前需要把VA=1,如果不做，等于瞎忙活，因为回到A的流程里还是要判断这个值)
			
			3）pthreadc_cond_signal发送“信号”给任意一个等待线程；pthread_cond_broadcast发送“信号”给所有等待线程
   
   DEMO说明：子线程1~n阻塞等待“信号”（信号由主线程通过pthreadc_cond_signal/pthread_cond_broadcast产生），一旦为10则输出依次当前时间，然后继续等待A变为10,
	     主线程获取随机数，如果是10的整数倍，那么发送条件变量给任意一个等待这个条件变量的线程(本例中即为主线程)
*/

#include "mythread.h"

#define DEF_NUM 5 //5个子线程

int ZC=0;


pthread_mutex_t wakeup_mutex;
pthread_cond_t wakeup_cond;



void do_something(struct thread_stu * args)
{
	printf("do_something\n",args->thread_workid,args->thread_tid);
}

void* func(void* args)
{
	struct thread_stu *tmp;
	
	tmp=(struct thread_stu *)args;
    while(1)
    {
		pthread_mutex_lock(&wakeup_mutex);
		/*wait会解锁互斥量，这个函数相当于“解锁互斥量，设置锚点wakeup_cond，同时阻塞等待通知”*/
		/*阻塞等待在这里，注意不是忙等*/
			printf("WORKID[%d]waitting..........\n",tmp->thread_workid);
			pthread_cond_wait(&wakeup_cond,&wakeup_mutex);
			printf("WORKID[%d]stop wait\n",tmp->thread_workid);
		do_something((struct thread_stu *)args);
		pthread_mutex_unlock(&wakeup_mutex);
    }
	
}

int main(int argc,char ** argv)
{
	int i;
	long ran;
	struct thread_stu st[DEF_NUM];
	pthread_mutex_init(&wakeup_mutex,NULL);
	pthread_cond_init(&wakeup_cond,NULL);

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

	sleep(1);
	printf("wait for all the child thread get up&wait for condition.\n");
	sleep(1);

	long B;
	long A;
    while(1)
    {
	/*因为所有子线程都在wait，所以父线程一进来就能拿到这个锁*/
	pthread_mutex_lock(&wakeup_mutex);
	/*一但主线程走到while，就代表所有子线程都没有持锁的，都是阻塞等待的，不吃CPU*/
	/*如果这里不采用主线程满足条件，而是在信号处理函数中满足，这样主线程也不用再占用CPU,这是最好的情况*/
	/*呈上，如果这里采用select，epoll模型，那么由于这些函数不吃CPU，这个网络模型是最合适的*/

	    /*这个while即使用来模拟一个条件的，完全可以删掉，然后疯狂pthread_cond_broadcast和pthread_cond_signal,所有子线程会疯狂被触发*/
		while(1)
		{
		/*在实际应用中，这里应该是一个阻塞状态，等待某个事情发生后，继续向下执行，从而能够进入pthread_cond_broadcast/pthread_cond_singnal函数
		  进而，能够像其他等待cond的子线程发送信号*/

			B=random();
			//sleep(1);
			A=B%100;
			if(A)
			{
				ZC=0;	/*不能整除，继续循环*/
				continue;
				
			}
			else 
			{
				ZC=1;	/*整除，跳出循环，通知一个等待条件变量的线程*/
				break;	
			}
		}
	printf("RANDOM=%ld\n",B);
	/*通知*/
	pthread_cond_broadcast(&wakeup_cond);
	pthread_mutex_unlock(&wakeup_mutex);
	sleep(1);  //这里做一个sleep，目的是为了防止主线程疯狂抢占互斥量，导致子线程无法设置pthread_cond_wait,试验中，如果不设置，貌似子线程根本抢不到
    }
}















