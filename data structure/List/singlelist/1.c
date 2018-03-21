#include "1.h"

int main(int argc,char ** argv)
{
        struct single_link *tmp;
        initlink(&tmp,10,0);


        printflink(tmp);
}


int initlink(struct single_link **out,int total,int value)
{
        struct single_link *head,*tmp;
        int i;
        //head node
        head = (struct single_link *)malloc(sizeof(struct single_link));
        if(head == NULL)
                {
                        printf("malloc error\n");
                        return -1;
                }
        tmp=head;

        //other nodes
        for(i=1;i<total;i++)
        {
                tmp->next = (struct single_link *)malloc(sizeof(struct single_link));
                if(tmp->next == NULL)
                        {
                                printf("malloc error\n");
                                return -1;
                        }
                tmp->value=value;
                tmp->seq=i;
                tmp=tmp->next;
        }
        //last node
        tmp->seq=i++;
        tmp->value=value;
        tmp->next=NULL;

        *out=head;
        return 0;
}


int printflink(struct single_link *tmp)
{
        struct single_link * in;
        in=tmp;

        while(in->next!=NULL)
        {
                printf("|%p|%d|%d|----->",in->next,in->value,in->seq);
                in=in->next;
        }
        printf("|NULL|%d|%d|\n",in->value,in->seq);
}
