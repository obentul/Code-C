#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#define IN_KEY 6666  //本进程的写入内存区
#define OUT_KEY 7777 //本进程的读出内存区
#define IN_SIZE 2048 //写入缓冲区大小
#define OUT_SIZE 2048 //读出缓冲区大小 

int main(int argc ,char ** argv)
{
	int in_id,out_id;	
	char *in_mem,*out_mem;
	char out_buf[2049];
	char c_random;

	if(argc!=2)
	{
		return -1;
	}

	if(argv[1][0]=='1') goto xxx;
	if(argv[1][0]=='2') goto yyy;
	

	memset(out_buf,0x00,2049);

xxx:
	in_id=shmget(IN_KEY,2048,IPC_CREAT|IPC_EXCL);	//创建共享内存
	if(in_id==-1)					//共享内存已创建，打开共享内存区
	in_id=shmget(IN_KEY,2048,0);			//打开共享内存区
	
	out_id=shmget(OUT_KEY,2048,IPC_CREAT|IPC_EXCL);
	if(out_id==-1)
        out_id=shmget(OUT_KEY,2048,0);

	in_mem = shmat(in_id,0,0);
	out_mem = shmat(out_id,0,0);
	while(1)
	{
		c_random = 'x';
		

		memset(in_mem,c_random,2048);
		memcpy(out_buf,out_mem,2048);
		printf("%s\n",out_buf);
		sleep(3);
	}

yyy:
        in_id=shmget(IN_KEY,2048,IPC_CREAT|IPC_EXCL);
	if(in_id==-1)
	in_id=shmget(IN_KEY,2048,0);

	out_id=shmget(OUT_KEY,2048,IPC_CREAT|IPC_EXCL);
	if(out_id==-1)
	out_id=shmget(OUT_KEY,2048,0);

	in_mem = shmat(in_id,0,0);
	out_mem = shmat(out_id,0,0);
	while(1)
	{

		c_random = 'y';
		memset(out_mem,c_random,2048);		
	 	memcpy(out_buf,in_mem,2048);
	  	printf("%s\n",out_buf);
	  	sleep(3);
	}
}


//描述：简单的使用共享内存完成进程间通讯的例子，需要注意创建和打开共享内存区时，虽然都是使用shmget函数，但是参数是不同的
////使用方法：./1 1    ./1 2
////效果：./1 1的终端上持续输出y，./1 2的终端上持续输出x
