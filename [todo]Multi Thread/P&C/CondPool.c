/* 1个TABLE，内含DEF_NODE_NUM个NODE。
*  主线程负责所有节点的填充工作
*  子线程按照数量被划分出来管理不同的节点区间，设置一个条件变量监控区间内的节点，然后“打酱油”等待主线程通知自己
*	此外，还有几个模型分类：1.主线程随即唤醒一个线程，这样的话（因为本模型的主线程每次只“质问”一个节点，因此采用唤醒一个线程的模式）
								（这里有个疑问，如果所有线程都在处理中，那么主线程再唤醒的时候，已经没有空闲线程了，此时怎么办）
							2.主线程唤醒所有线程来（如果主线程通过epoll来质问多个节点，采用这个模型可能会好点）
*/

#include "mythread.h"

#define DEF_NODE_NUM 500
#define DEF_THREAD_NUM 50

void producer(void);
void* consumer(void *args);
void init_table(void);
void workwork_2(int fd,int index,struct thread_stu* args);
int workwork_1(int fd);


/*******************************************************************/
/***************************节点************************************/
struct Node{
        /*protected this node*/
        pthread_mutex_t available;	//互斥量

        /*value*/
        int rfd;        //>0可用,-1不可用
        int wfd;

        /*node next*/
	int index;              //在表中的位置(暂时只用作调试)
        struct Node * next;     //此版为数组结构的表(目前没用到，暂时保留，后期如果做成链表结构，再启用)
};

/*******************************************************************/
/***************************条件变量********************************/
pthread_cond_t wakeup_cond;
pthread_mutex_t wakeup_mutex;

/*******************************************************************/
/*****************************表************************************/
struct Table{
	/*table properties*/

	/*table value*/
        struct Node ND[DEF_NODE_NUM]; 	//DEF_NODE_NUM个节点
}TB1;

/*******************************************************************/
/*************************消费线程功能函数*************************/
struct consumer_func{
	/*rfd func*/
	int (*func1)(int);	//void 返回值，int参数的指针
	void (*func2)(int,int,struct thread_stu*);	//void 返回值，void参数的指针
	
	/*wfd func*/
};
static struct consumer_func cf = {
	/*rfd func*/
	.func1=workwork_1,
	.func2=workwork_2
	
	/*wfd func*/
};

/*******************************************************************/
/*************************生产线程功能函数**************************/
struct producer_func{
	/*rfd func*/
	
	/*wfd func*/
	
};


/*******************************************************************/
/*******************生产者线程执行程序******************************/
void producer(void)
{
        int i=0,ret,j=10;
		
	while(1)
	{
        again_producer:
        /*锁住节点*/
        ret = pthread_mutex_trylock(&(TB1.ND[i].available));
        if((ret == 0) && (TB1.ND[i].rfd==-1))
        {
			TB1.ND[i].rfd=j++;	//给一个随机值
			pthread_mutex_unlock(&(TB1.ND[i].available));
        }
        /*节点不可用，向下轮询*/
        else
        {
			if(ret == 0)
		   {
				pthread_mutex_unlock(&(TB1.ND[i].available));  
		   }
           if(i==DEF_NODE_NUM)
           {
				i=0;
           }
           else
           {
				i++;
           }
		   //sleep(1); //睡1s后继续执行
           goto again_producer;
        }
	}
}

/*******************************************************************/
/*******************消费者线程执行程序******************************/
void* consumer(void *args)
{
        int i=0,ret,l;
        pthread_detach(pthread_self());	//不再有主线程回收

	while(1)
	{	


        again_consumer:
        /*锁住节点*/
        ret = pthread_mutex_trylock(&(TB1.ND[i].available));
        if((ret == 0) && (TB1.ND[i].rfd!=-1))
        {
			/***************输出如下内容：*******************************
							"i'm #[%d] thread , get node , fd is [%d]\n"
			*************************************************************/
			cf.func2(TB1.ND[i].rfd,TB1.ND[i].index,(struct thread_stu*)args);	//使用workwork_2
			
			
			TB1.ND[i].rfd=-1;	//还原节点为不可用
			pthread_mutex_unlock(&(TB1.ND[i].available));
        }
        /*节点不可用，向下轮询*/
        else
        {
			pthread_cond_wait(&wakeup_cond,&wakeup_mutex);
			
			
		   if(ret == 0)
		   {
				pthread_mutex_unlock(&(TB1.ND[i].available));  
		   }
           if(i==DEF_NODE_NUM)
           {
				i=0;
           }
           else
           {
				i++;
           }
		   //sleep(1);
           goto again_consumer;
        }
	}
}


/*******************************************************************/
/*******************生产者 & 消费者的功能函数***********************/
/*********拿到资源以后，进入不同的功能函数完成不同的任务************/
int workwork_1(int fd)
{
	int i,n;
	char buf[8192];
	/*从文件描述符中读数据*/
 	again_workwork_1:
	n=read(fd,buf,8192);
	if((n!=0)&&(n!=-1))
	{
        	i=i+n;
         	goto again_workwork_1;
 	}
 	else if(n==0)
	{
         	i=0;
         	printf("read done\n");

         	/*处理消息*/
         	//dosomething();
 	}
 	else
 	{
        	pthread_mutex_unlock(&(TB1.ND[i].available));
        	perror("read error");
        	return -1;
 	}
}
void workwork_2(int fd,int index,struct thread_stu* args)
{
	printf("WORKID[%d],get node index = [%d],rfd is [%d],thread#[%ld]\n",args->thread_workid,index,fd,pthread_self());
	sleep(1);
}


/*******************************************************************/
/****************************其他函数*******************************/
void init_table(void)
{
	int i;
	for(i=0;i<DEF_NODE_NUM;i++)
	{
		pthread_mutex_init(&TB1.ND[i].available,NULL);
		TB1.ND[i].index=i;
		TB1.ND[i].rfd=-1;
		TB1.ND[i].wfd=-1;
	}
}









int main(int argc,char ** argv)
{
        int i;
        struct thread_stu st[DEF_THREAD_NUM];

		init_table();
		
        /*Thread Poll*/
        for(i=0;i<DEF_THREAD_NUM;i++)
        {
                st[i].thread_tid=0;
				st[i].thread_workid=i;
                st[i].thread_ret=NULL;
                st[i].thread_desc=NULL;
                st[i].args=&st[i];
                st[i].thread_func=consumer;

                pthread_create(&st[i].thread_tid,NULL,st[i].thread_func,st[i].args);
        }

        producer();
}








