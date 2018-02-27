1.c
```
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>

void print_bt(void)
{
     int j, nptrs;
     #define SIZE 100
     void *buffer[100];
     char **strings;

     nptrs = backtrace(buffer, SIZE);
     printf("backtrace() returned %d addresses\n", nptrs);

     /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
      * would produce similar output to the following: */

     strings = backtrace_symbols(buffer, nptrs);
     if (strings == NULL) {
         perror("backtrace_symbols");
         exit(1);
     }

     for (j = 0; j < nptrs; j++)
         printf("%s\n", strings[j]);

     free(strings);
}


void newhandle(int signo,siginfo_t *siginfo)
{
        int pid=getpid();

        print_bt();

        printf("signo = %d , siginfo->si_signo = %d , siginfo->si_pid vs pid = %d  vs %d\n ",signo,siginfo->si_signo,siginfo->si_pid,pid);

}

int main (int argc,char ** argv)
{

        struct sigaction newact,oldact;

        memset(&newact,0x00,sizeof(newact));
        newact.sa_flags = SA_SIGINFO;   //想获取siginfo_t必须制定这个flag
        newact.sa_sigaction = newhandle;

        sigaction(SIGSEGV,&newact,&oldact);

        //raise(SIGSEGV); //可以自己给自己发一个SIGSEGV信号

        while(1) sleep(1);

}
```

操作：  
gcc 1.c -o 1  
./1 &  
kill -11 [pid of 1]  

输出：  
./2() [0x40083f]  
./2() [0x4008e7]  
/lib64/libc.so.6(+0x35650) [0x7ffe9d81f650]  
/lib64/libc.so.6(nanosleep+0x10) [0x7ffe9d8a7470]  
/lib64/libc.so.6(sleep+0xd4) [0x7ffe9d8a7324]  
./2() [0x400978]  
/lib64/libc.so.6(__libc_start_main+0xf5) [0x7ffe9d80baf5]  
./2() [0x400759]  
signo = 11 , siginfo->si_signo = 11 , siginfo->si_pid vs pid = 8281  vs 29525  
  
参考：  
http://www.cnblogs.com/sxhlinux/p/6729384.html
