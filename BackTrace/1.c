//可通过如下代码输出调用栈信息：

#include <execinfo.h>
#include <unistd.h>
#include <stdlib.h>

void bt(void)
{
     int j, nptrs;
     #define SIZE 100
     void *buffer[100];
     char **strings;

     nptrs = backtrace(buffer, SIZE);
     printf("backtrace() returned %d addresses\n", nptrs);

     // The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
     //     would produce similar output to the following:

     strings = backtrace_symbols(buffer, nptrs);
     if (strings == NULL) {
         perror("backtrace_symbols");
         exit(1);
     }

     for (j = 0; j < nptrs; j++)
         printf("%s\n", strings[j]);

     free(strings);
}

void func2()
{
	bt();
	while(1) sleep(1);
}

void func1()
{
	func2();
}


int main(int argc,char ** argv)
{
	func1();
}


