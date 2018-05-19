#include <stdio.h>

void func1(void);

int main(int argc,char ** argv)
{
	extern int i;			//编译不通过，i在main的栈里，func1不可见
	func1();
}

void func1(void)
{
	printf("func1_i=%d\n",i);	//看不到变量i
}



/* 小结；对于extern而言，就相当于在当前使用位置定义了这个变量，如果在某个函数的栈里，那么别的函数是看不到的
 * 如果是在函数体外部，且在文件的最头部，那么整个文件都可以看得到，如果是穿插在文件的函数体之间的外部，那么只有
 * 后面的函数体能看的到
 *
 * 简言之：extern位置决定了变量的作用域，完全等价于新定义一个变量，这个变量在什么位置决定了其作用域。
 * */
