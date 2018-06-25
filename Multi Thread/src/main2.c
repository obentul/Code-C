 /* 说明：创建子线程，然后在子线程里注册线程清理函数，主线程挥手子线程的退出返回值
  * 期待结果：
  *           clean up #0 ---[11]---
  *           clean up #1 ---[12]---
  *           ++++++first job over++++++
  * 实际结果： 与期待结果一致
  *
  *
  * */

 #include "mythread.h"

 void* do_job(void *args);
 void do_cleanup_0(void *args);
 void do_cleanup_1(void *args);

 void* do_job(void *args)
 {
         struct thread_stu * args1=args;
         pthread_cleanup_push(args1->thread_cleanup[0],args1->cleanup_args[0]);
         pthread_cleanup_push(args1->thread_cleanup[1],args1->cleanup_args[1]);
         pthread_cleanup_pop(1);
         pthread_cleanup_pop(1);
         pthread_exit("first job over");
 }

 void do_cleanup_0(void *args)
 {
         printf("clean up #0 ---[%d]---\n",*(int *)args);
 }

 void do_cleanup_1(void *args)
 {
         printf("clean up #1 ---[%d]---\n",*(int *)args);
 }

 int main(int argc,char ** argv)
 {
         struct thread_stu st1;

         int args=10;
         int cleanup_args_0=11;
         int cleanup_args_1=12;

         st1.thread_tid=0;
         st1.thread_ret=NULL;
         st1.thread_desc="first job\n";
         st1.args=&st1;  //把自己的结构体地址作为参数，以方便使用各种函数(这样设计很合理)
         st1.cleanup_args[0]=&cleanup_args_0;
         st1.cleanup_args[1]=&cleanup_args_1;

         st1.thread_func=do_job;
         st1.thread_cleanup[0]=do_cleanup_0;
         st1.thread_cleanup[1]=do_cleanup_1;

         //通过最后一个参数给线程传参，这里不用考虑主线程栈和子线程栈独立的问题，这个设计很好，不知道底层是如何实现的？
         pthread_create(&st1.thread_tid,NULL,(void *)st1.thread_func,st1.args); 

         pthread_join(st1.thread_tid,&st1.thread_ret);

         printf("++++++%s++++++\n",st1.thread_ret);
         while(1) sleep(1);
 }
