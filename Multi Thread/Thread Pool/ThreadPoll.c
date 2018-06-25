/* 1个TABLE，内含DEF_NODE_NUM个NODE。主线程循环填充NODE(大于DEF_NODE_NUM则停止填充，等待有空闲的节点)。子线程轮询TABLE内的每一个节点，找到
*  未被上锁的节点，加锁，读取其中的内容，完成一系列工作，然后标注节点为空闲并释放锁，接着继续轮询。
*
*/


#include "mythread.h"

#define DEF_NODE_NUM 500
#define DEF_THREAD_NUM 20

struct Node{
        /*protected this node*/
        pthread_mutex_t available;

        /*value*/
        int rfd;        //>0可用,-1不可用
        int wfd;

        /*node next*/
        struct Node * next;     //目前没用到，暂时保留
}

struct Table{
        
        struct Node[DEF_NUM]; //默认500个节点
}TB1;


int main(int argc,char ** argv)
{
        int i;
        struct thread_stu st[DEF_THREAD_NUM];


        memset(st,0x00,DEF_THREAD_NUM*sizeof(struct thread_stu));

        /*Thread Poll*/
        for(i=0;i<DEF_THREAD_NUM;i++)
        {
                st[i].thread_id=0;
                st[i].thread_ret=NULL;
                st[i].thread_desc=NULL;
                st[i].args=&st[i];
                st[i].thread_func=consumer;

                pthread_create(st[i].thread_tid,NULL,st[i].thread)func,st[i].args);
        }

        producer();

}

void producer(void)
{

}

void* consumer(void *args)
{
        char buf[8192];
        int i=0,ret,n;
        pthread_detach(pthread_self());

        again:
        /*锁住节点*/
        ret = pthread_mutex_trylock(&(TB1.Node[i].available));
        if((ret == 0) && (TB1.Node[i].rfd!=-1))
        {
                /*从文件描述符中读数据*/
                again1:
                n=read(TB1.Node[i].rfd,buf,8192);
                if((n!=0)&&(n!=-1))
                {
                        i=i+n;
                        goto again;
                }
                else if(n==0)
                {
                        i=0;
                        printf("read done\n");

                        /*处理消息*/
                        workwork();

                        /*写回rfd*/
                        write();
                }
                else
                {
                        pthread_mutex_unlock(&(TB1.Node[i].available));
                        perror("read error");
                        return -1;
                }
        }
        pthread_mutex_unlock(&(TB1.Node[i].available));

        /*节点不可用，向下轮询*/
        else
        {
                if(i==DEF_NODE_NUM)
                {
                        i=0;
                }
                else
                {
                        i++;
                }
                goto again;
        }

}

void workwork(void)
{

}
