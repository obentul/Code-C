#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
 * RIGHT
*/
void GetMemory(char ** p)
{
        *p=(char *)malloc(100);
}


int main(int argc,char ** argv)
{
        char *str=NULL;
        GetMemory(&str);
        strcpy(str,"hello world\n");
        printf("%s",str);
}




/*
 * WRONG
 * Segment fault

void GetMemory(char *p)
{
        p=(char *)malloc(100);
}

int main(int argc,char ** argv)
{
        char *str=NULL;
        GetMemory(str);
        strcpy(str,"hello world\n");
        printf("%s",str);
}
*/

