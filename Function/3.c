//函数入参为数组时，其实就是函数指针，如果入参为指针时，同样可以按照数组的操作方法来使用
//因此对于函数入参来说， 指针就是数组，数组就是指针

#include <stdio.h>

int func(int a[]);
int func1(int *a);

int main (int argc,char ** argv)
{
    int a[2]={0,1};

    func(a);
    func1(a);
}


int func(int a[])
{
    printf("%d\n",a[1]);
}

int func1(int *a)
{
    printf("%d\n",a[1]);
}
