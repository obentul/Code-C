#include <unistd.h>
#include <stdlib.h>

/* ./yk &
 * ps -ef|grep yk
 * 可以看到yk进程的父进程为当前终端进程
 *
 * 实验1：
 * kill -9 终端进程pid
 * 在另外一台终端上ps -ef|grep yk，会发现yk依旧存在，只是父进程变为1号进程
 *
 * 实验2：
 * exit
 * 在另外一台终端上ps -ef|grep yk，会发现yk依旧存在，只是父进程变为1号进程
 *
 * 实验3：
 * kill -1 终端进程pid
 * 在另外一台终端上ps -ef|grep yk，yk已经不再存在
 *
 *
 * */



int main()
{
    while(1) sleep(1);
}
