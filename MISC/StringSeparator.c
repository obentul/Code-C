#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int separatorstr(char* src, char separator, int index, char **dest)
{
        if (src == NULL)
        {
                return -1;
        }
        char *head, *tail;
        head = src;
        tail = src;
        int i = 0;

        while (tail != '\0')
        {
                if (*tail == separator){
                        if (i == index){
                                tail--;
                                int len = (int)(tail - head) + 1;
                                memcpy(dest, head, len);
                                return 0;
                        }
                        else{
                                head = ++tail;
                                i++;
                                continue;
                        }
                }
                tail++;
        }
        return -1;
}


int main(int argc,char ** argv)
{

        char *src = "123;456;789";
        char dest[10];

        memset(dest,0x00,10);

        separatorstr(src,';',1,&dest);  //从0开始计算，123的index是0，456的index是1

        printf("--->  %s  <---\n",dest);



}
