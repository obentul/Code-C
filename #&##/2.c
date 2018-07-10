#include <stdio.h>

/* ##相当于简单的黏合，本例中就直接把y和k直接拼接在一起，从而实现了一个叫做yk的char指针
 * */

#define MAKE_NAME(xing,ming) xing ## ming 


int main()
{
	char *MAKE_NAME(y,k)="yangkun\n";
	printf("%s\n",yk);
}
