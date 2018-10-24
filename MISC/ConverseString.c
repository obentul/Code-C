#include <stdio.h>
#include <string.h>

int converse(char *s);

int main (int argc,char ** argv)
{
    char s[10]="123456789";

    printf("BEFORE: %s\n",s);

    converse(s);

    printf("AFTER: %s\n",s);

}


int converse(char *s)
{
    if(s==NULL)
    {
        printf("s is NULL, error\n");
        return -1;
    }

    int len,i;
    char *p_h,*p_t;
    char swap;

    len = strlen(s);
    p_h = s;
    p_t = s+len-1;

    for(i=0;i<len/2;i++)
    {
       p_h = p_h + i;
       p_t = p_t - i;
       swap = *p_h;
       *p_h = *p_t;
       *p_t = swap;
    }
    
    return 0;
}
