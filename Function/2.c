#include <stdio.h>

void (*p) (int,int);

void printlarger(int a,int b)
{
    int c;
    c=(a>=b?a:b);
    printf("larger one is [%d]\n",c);
}

int main(int argc,char **argv)
{
    int a,b;
    printf("need two int value:\n");
    scanf("%d",&a);
    scanf("%d",&b);

    /*直接调用*/
    printlarger(a,b);

    /*指针调用*/
    p=&printlarger;
    p(a,b);

    return 0;
}

/*
小结：定义函数指针时，先写函数的返回值和入参类型，然后在中间加上(*指针名)  
     指针的赋值，指针需要指向相应的函数，因此需要获得函数的地址  
     使用起来，和使用函数名一样  
*/
