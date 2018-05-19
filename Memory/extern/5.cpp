#include <stdio.h>

void func(void);

int main(int argc,char ** argv)
{
	extern int i;
	printf("main_i=%p\n",&i);
	
	func();
}

void func(void)
{
	extern int i;
	printf("func_i=%p\n",&i);
}



/* 运行结果：
 * main_i=0x601034
 * func_i=0x601034
 *
 * objdump -t结果：
 * 0000000000601034 g     O .data  0000000000000004              i
 *
 *
 * 小结： 1. 在不同的栈中声明，变量的地址是一样的
 *        2. 在符号表中，即使是在函数栈中通过extern引用外部变量，此符号表还是属于data段，为此变量最初在extern.c中声明的一样
 *        3. 综合可见，extern继承了作用范围，即在某个函数栈中引用并不会导致别的函数栈也可以引用得到。但是在符号表中，无论有
 *           多少次extern声明，只有一个符号表，这个符号表的属性和变量最原始定义时是一样的(extern.c中)。
 *           
 *           具体的原理参见5.txt
 * */
