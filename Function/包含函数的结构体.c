#include <stdio.h>  

static void printint(int a);
static void printchar(char a);

struct stu_many_print_func{
    /*函数指针调用*/
    void (*pfint) (int);
    void (*pfchar) (char);
};

struct stu_many_print_func many_print_func = {
    .pfint=&printint,
    .pfchar=&printchar,

 /*可以写为
 *
 *         .pfint=printint;
 *             .pfchar=printchar;
 *  */
};

static void printint(int a)
{
    printf("%d\n",a);
}

static void printchar(char a)
{
    printf("%c\n",a);
}

int main (int argc, char ** argv)
{
    int a=10;
    char b='b';
    many_print_func.pfint(a);
    many_print_func.pfchar(b);

}  

/*
注：  
1.函数名只可以赋值给函数指针，对于函数static void printint(int a)，printint  和  &printint都表示函数地址，所以"只能取函数地址赋值  
给函数指针的方式来使用";
2.结构体定义，每个成员的后面都要跟“分号”；结构体赋值，每个成员后面都要跟“逗号”  
*/  
    
