/*说明：1.创建一个内存表Table，有N个Node组成，Node节点为链表
 *      2.主线程每1秒向Table中增加一个Node到尾部(监听进程accept每返回一次，就把返回值填入链表)
 *      3.创建N个线程的线程池，
 *
 *
 * */

#include <pthread.h>

#define DEEPTH 20       //线程池的深度
#define INIT 500        //初始节点数为500

struct Node *tablehead;

struct Node;

struct Node{
        pthread_mutex_t avail;  //当前节点是否已经被锁上
        int fd;
        struct Node *next=NULL;
};

struct Table{
        int total=INIT; //总条目数
        int dirty;      //当前已使用的Node数

        struct Node *node_1st;  //首节点

        pthread_mutex_t lock;
}table1;

int main(int argc,char ** argv)
{
        int j;
        memset(&table1,0x00,sizeof(struct Table));

        //1.初始化INIT个Node的Table
        for(j=0;j<table1.total-1;j++)
        {
                struct Node *tmp;
                tmp = malloc(sizeof(struct Node));
                memset(tmp,0x00,sizeof(struct Node));
                tmp->next==NULL;
        }

        //2.创建线程池
        for(i=0;i<DEEPTH;i++)

        //3.每隔1秒填表一次
        if(1)
        {
                fill();
                sleep(1);
        }


}
