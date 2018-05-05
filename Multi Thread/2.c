#include <pthread.h>
#include <stdio.h>


typedef struct{
        void (*func) (void);
        pthread_t tid;
        void *ret;
        char *desc;
}thread_stu;


void thread1_func(void)
{
        char *ret="thread1 recorder exit\n";
        printf("i am the recorder\n");
        pthread_exit(ret);
}


int main (int argc,char ** argv)
{
        thread_stu thread1;
        thread1.desc="process percentage recorder\n";
        thread1.func=thread1_func;

        pthread_create(&thread1.tid,NULL,(void *)thread1.func,NULL);
        pthread_join(thread1.tid,&thread1.ret);
        printf("%s\n",thread1.ret);
}
