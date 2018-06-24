#include "doublelist.h"

int main(int argc,char ** argv)
{
        struct double_link *tmp;
        initlink(&tmp,5,8);
        printflink(tmp);
        printf("%d\n",lenlink(tmp));
        printf("\n");

        printf("insert a node to the 3rd node's left value=9:\n");
        insertlink(tmp,3,-1,9);
        printflink(tmp);
        printf("LEN=%d\n",lenlink(tmp));
        printf("\n");

        printf("insert a node to the 1st node's left value=9:\n");
        insertlink(tmp,1,-1,9);
        printflink(tmp);
        printf("LEN=%d\n",lenlink(tmp));
        printf("\n");

        printf("delete the first node from link list:\n");
        deletenode_by_seq(tmp,1);
        printflink(tmp);
        printf("\n");

        return 0;
}
