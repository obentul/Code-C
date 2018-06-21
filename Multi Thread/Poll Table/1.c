#include <pthread.h>

#define DEEPTH 20	//线程池的深度
#define INIT 500	//初始节点数为500

struct Node *tablehead;

struct Node;

struct Node{
	pthread_mutex_t avail;
	int fd;
	struct Node *next=NULL;
};

struct Table{
	int total=INIT;	//总条目数
	int dirty;	//当前已使用的Node数

	struct Node *node_1st;	//500个条目供轮询

	pthread_mutex_t lock;
}table1;

int main(int argc,char ** argv)
{
	int j;

	//1.初始化被扫表
	memset(&table1,0x00,sizeof(struct Table));
	

	for(j=0;j<table1.total-1;j++)
	{
		struct Node *tmp;
		tmp = malloc(sizeof(struct Node));
		memset();
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
