#ifndef _DOUBLELIST_H_
#define _DOUBLELIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*data structure*/
struct double_link{
        int seq;
        int value;
        struct double_link * pre;
        struct double_link * next;
};

//finished
int initlink(struct double_link **out,int total,int value);
int printflink(struct double_link *tmp);
int lenlink(struct double_link * tmp);
int insertlink(struct double_link *tmp,int seq,int orient,int value);
int deletenode_by_seq(struct double_link *tmp,int seq);
int destorylink(struct double_link *tmp);
int reverselink(struct double_link *tmp,struct double_link **new);
//todo
int deletenode_by_value(struct double_link *tmp,int value);
int sortlink(struct double_link *tmp,struct double_link *new,int orient);

#endif
