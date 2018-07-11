#include <stdio.h>
#include <unistd.h>


int main()
{
	printf("xxx\n");
	while(1) sleep(1);
}




/*   [root@localhost 程序员的自我修养]# ./yk &
 *   [1] 23602
 *   xxx
 *   [root@localhost 程序员的自我修养]# lsof -p 23602
 *   COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF      NODE NAME
 *   yk      23602 root  cwd    DIR  253,2       25 671399942 /home/yangkun/Git/Code/程序员的自我修养
 *   yk      23602 root  rtd    DIR  253,0     4096      1024 /
 *   yk      23602 root  txt    REG  253,2     8598 671593532 /home/yangkun/Git/Code/程序员的自我修养/yk
 *   yk      23602 root  mem    REG  253,0  2112384 252618805 /usr/lib64/libc-2.17.so
 *   yk      23602 root  mem    REG  253,0   164440 253519134 /usr/lib64/ld-2.17.so
 *   yk      23602 root    0u   CHR 136,12      0t0        15 /dev/pts/12
 *   yk      23602 root    1u   CHR 136,12      0t0        15 /dev/pts/12
 *   yk      23602 root    2u   CHR 136,12      0t0        15 /dev/pts/12
 *
 *
 *   扩展：1.通过lsof命令可以看到，当前可执行文件代开了动态库：/usr/lib64/libc-2.17.so和/usr/lib64/ld-2.17.so，可见本程序使用了这两个动态库
 *	   2./usr/lib64/libc-2.17.so提供了printf和sleep，/usr/lib64/ld-2.17.so提供了链接工具
 *	   3.上述库都属于glibc库，glibc有且仅有N多个.so动态库，是系统的最基本库集合。
 *  
 *
 * 
 *
 *
 * */
