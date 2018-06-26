#ifndef _MYTHREAD_H_
#define _MYTHREAD_H_


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define CLEANUP_MAX 3

int lock_read(int fd,void *buf,size_t count,pthread_mutex_t *mutex);
int lock_write(int fd,void *buf,size_t count,pthread_mutex_t *mutex);

struct thread_stu;

typedef void vvx_func(void *args);   //入参void，返回void *
typedef void* vxvx_func(void *args);   //入参void*，返回void *
typedef void vv_func(void args);   //入参void，返回void

struct thread_stu{
        pthread_t thread_tid;           //线程id
	int thread_workid;			//线程池场景中，方便观察的线程工号
        void *thread_ret;               //返回值
        char *thread_desc;              //线程描述
        struct thread_stu *args;                        //创建线程入参
        void *cleanup_args[CLEANUP_MAX];                //清理函数入参


        vxvx_func *thread_func; //线程执行函数
        vvx_func *thread_cleanup[CLEANUP_MAX];     //线程退出清理函数,指针数组
};


#endif
