//说明；1）对于semctl函数，原型为：int semctl(int semid, int semnum, int cmd, ...);
//      第四个参数是“联合体”union semun，因为是联合体，所以每次只能是一种形态，而每种形态正好对应了第三个参数cmd的不同值，具体可使用man来查看细节
//      本例子中使用了SETVAL来给信号量初始化一个值
//      	(注意：这个union联合体是需要自己定义的！！！！，参见正文中自己定了联合体)
//
//
//
//	2）对于semop函数，原型为：int semop(int semid, struct sembuf sops[], unsigned nsops);   
//					或者
//			       int semop(int semid, struct sembuf *sops, unsigned nsops);
//	第二个参数是一个结构体数组/指针(这里可以看出来入参指定为数组的好处，让使用者看起来更直接)，这也印证了"信号量是按照集合进行操作的"，每次会
//	传多个操作集合(数组)仅semop，这些集合中都制定了信号量编号，此函数会根据结构体数组，依次对这些信号量进行批量操作，当然了，如果不想操作某个
//	信号量，在数组中不指定此信号量的结构体即可。为保险起见，第三个参数nsops明确支出要操作几个信号量(和snprintf中的n一样，用来防止内存踩踏)
//
//
//结果：1.log文件中的日志无穿插，有序显示，信号量有效果，实现了进程间对共享资源的同步
//
//
//使用说明：清空1.log文件，连续多次运行可执行文件，输出内容可以再fprintf函数处修

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/ipc.h>
#include <fcntl.h>

#define KEY 7777

//(重点)这个联合体是要自己定义的
union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
                               (Linux-specific) */
};

struct semid_ds s1;	//用来从内核中拷贝信号量的描述结构体，需要配合semctl函数使用(本例中没列出)
struct sembuf op1;	//信号量操作结构体，semop函数只接受结构体入参，这个结构体中包含了信号量的编号(0~semnum-1),对信号量的操作，特殊标志位三个元素

int main(int argc,char ** argv)
{
	int semid;
	FILE* fd;
	union semun u1;	//初始化信号量集中的某个信号量而使用的"容器"
	
	memset(&op1,0x00,sizeof(struct sembuf));

	//1.创建信号量集，集合id为semid，集合中有3个信号量(0、1、2)
	//(一般情况下都是一个信号量集里面一个信号量，这样方便使用，信号量在最初设计的时候这里就是过度设计，此处创建3个是为了展示信号量是按照集合操作的)
	semid=semget(KEY,3,IPC_CREAT|IPC_EXCL|0666);
	if((semid==-1)&&(errno==EEXIST))
	{
		if(errno==EEXIST)
		{	
			//打开已创建的信号量集
			semid=semget(KEY,0,NULL);
		}
		else
		{
			return -1;
		}
	}
	else
	{	
		u1.val=1;	//第二个信号量1的初始值为1
		//初始化信号量集中的第二个信号量
		semctl(semid,1,SETVAL,u1.val);
	}
	//2.打开1.log
	fd=fopen("./1.log","a+");
	setvbuf(fd,NULL,_IOLBF,NULL);	//修改缓冲类型为行缓冲	

	int ret;
while(1)
    {
	int n;
	n=semctl(semid,1,GETVAL);
	//3.获取信号量，如果可用，给信号量-1
	op1.sem_num=1;	//第二个信号，编号为1
	op1.sem_op=-1;	//给信号量-1
	op1.sem_flg=IPC_NOWAIT; //不阻塞等待
	ret = semop(semid,&op1,1); //对信号量集semid中的编号为1的信号量执行操作
	if(ret==-1)
	{	
		if(errno=EAGAIN)
		{
			continue;
		}
		else
		{
			perror("error:");
			return -1;
		}
	}
	
	//4.输入10*10的PID
	int j;
	for(j=0;j<10;j++)
	{
		fprintf(fd,"----------------[%d]---------------\n",getpid());
	}

	//5.释放信号量
	op1.sem_num=1;
	op1.sem_op=1;	//+1
	op1.sem_flg=IPC_NOWAIT;
	ret = semop(semid,&op1,1); //让出资源，让其他进程抢占资源


	sleep(1);
    }

}

