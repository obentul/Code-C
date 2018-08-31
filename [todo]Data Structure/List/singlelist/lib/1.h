#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*data structure*/
struct single_link{
        struct single_link * next;
        int value;
        int seq;
};

//finished
int initlink(struct single_link **out,int total,int value);
int printflink(struct single_link *tmp);
int lenlink(struct single_link * tmp);
int insertlink(struct single_link *tmp,int seq,int orient,int value);
int deletenode_by_seq(struct single_link *tmp,int seq);
int destorylink(struct single_link *tmp);
int reverselink(struct single_link *tmp,struct single_link **new);
//todo
int deletenode_by_value(struct single_link *tmp,int value);
int sortlink(struct single_link *tmp,struct single_link *new,int orient);
