#include <stdio.h>


void func1(void);

int main(int argc,char ** argv)
{
	func1();
}

void func1(void)
{
	extern int i;
	printf("func1_i=%d\n",i);
}
