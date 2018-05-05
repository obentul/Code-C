#include <pthread.h>
#include <stdio.h>


typedef struct{
        void (*func) (void);
        pthread_t tid;
        void *ret;
        char *desc;
        void (*cleanup[32]) (void *arg);  //32个指向清理函数的指针（函数指针数组）
}thread_stu;

thread_stu thread1,thread2;

void cleanup_1st(void *arg)
{
        printf("cleanup_1st,arg = %s\n",(char *)arg);
}

void cleanup_2nd(void *arg)
{
        printf("cleanup_2nd,arg = %s\n",(char *)arg);
}

void thread1_func(void)
{
        char *ret="thread1 recorder exit\n";
        printf("i am the recorder\n");
        pthread_cleanup_push(thread1.cleanup[0],"first cleanup");
        pthread_cleanup_pop(0);
        pthread_exit(ret);
}

void thread2_func(void)
{
        char *ret="thread1 recorder exit\n";
        printf("i am the sleeper,i am falling aslee....\n");
        while(1) sleep(1);
}



int main (int argc,char ** argv)
{

        thread1.desc="process percentage recorder\n";
        thread1.func=thread1_func;
        thread1.cleanup[0]=cleanup_1st; //注册清理函数
        thread1.cleanup[1]=cleanup_2nd; //注册清理函数

        thread2.desc="i am born to sleep,i like slee... p\n";
        thread2.func=thread2_func;

        pthread_create(&thread1.tid,NULL,(void *)thread1.func,NULL);
        pthread_create(&thread2.tid,NULL,(void *)thread2.func,NULL);

        pthread_cancel(thread2.tid);

        pthread_join(thread2.tid,&thread2.ret);
        printf("%d\n",thread2.ret);
}
