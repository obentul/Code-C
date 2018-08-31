//说明：如何在预编译语句中使用被预编译的对象值

#include <stdio.h>
#include <unistd.h>

/* 如果想在字符串里在此引用x，那么需要使用"#x"来替代即可
 *
 *
 * */


#define PRINT_SQU_0(x) do{printf("x -> \"x\" de pingfang = %d \n",x*x);}while(0)
#define PRINT_SQU_1(x) do{printf("x -> "#x" de pingfang = %d \n",x*x);}while(0)

int main()
{
	PRINT_SQU_0(2);	//  x -> "x" de pingfang = 4
	PRINT_SQU_1(2); //  x -> 2 de pingfang = 4

	while(1) sleep(1);
}
