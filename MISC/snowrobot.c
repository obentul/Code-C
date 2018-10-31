#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct point;

struct point{
    int x;              //坐标x
    int y;              //坐标y
    char show;          // - + |
    struct point *next; //下一个点的指针
};

struct point * c_p_p=NULL;  //当前的机器人所在的位置
struct point start_point;

char map[11*12]={};
char BUFFER[2048];



void init_map();
void disp_map();
int check();





int main(int argc,char **argv)
{
    memset(map,'0',sizeof(map));
    start_point.x=0;
    start_point.y=0;
    start_point.next=NULL;
    c_p_p = &start_point;
    setvbuf(stdout,BUFFER,_IOFBF,2048);

    init_map();

    while(1)
    {
        disp_map();
        sleep(1);
        system("clear");
    }


    destory_all();
}

void init_map(){
     int i=0;

     map[(11-1)/2*12+(11-1)/2]='-';
     for(i=0;i<11;i++)
     {
        map[11*(i+1)+i]='\n';
     }
}

void disp_map(){
    write(1,map,11*12);
    fflush(stdout);
}

int locate_map(int x,int y){
    return 1; 
}

int check(){
    struct point *tmp;
    tmp = &start_point;
    while(tmp->next!=NULL){
        if(c_p_p->x==tmp->x)
        {
            if(c_p_p->y==tmp->y);
            printf("whoops!");
            return -1;
        }
        tmp=tmp->next;
    }
    printf("good!");
    return 0;
}


void go_left(int steps){
    int i;
    for(i=0;i<steps;i++)
    {
        struct point *p_p = (struct point *)malloc(sizeof(struct point));   //创建一个新点
        p_p->next = NULL;                                                   //这个点的下一个步尚且未知
        p_p->x = (c_p_p->x)-1;                                                //新点的x坐标：当前点的坐标-1
        p_p->y = c_p_p->y;                                                    //新店的Y坐标：不变
        c_p_p->next = p_p;                                                  //链表串起来
        c_p_p = p_p;                                                        //新的当前位置
    }
}
void go_right(int steps){
    int i;
    for(i=0;i<steps;i++)
    {
        struct point *p_p = (struct point *)malloc(sizeof(struct point));   //创建一个新点
        p_p->next = NULL;                                                   //这个点的下一个步尚且未知
        p_p->x = (c_p_p->x)+1;                                                //新点的x坐标：当前点的坐标+1
        p_p->y = c_p_p->y;                                                    //新店的Y坐标：不变
        c_p_p->next = p_p;                                                  //链表串起来
        c_p_p = p_p;                                                        //新的当前位置
    }
}

void go_up(int steps){
    int i;
    for(i=0;i<steps;i++)
    {
        struct point *p_p = (struct point *)malloc(sizeof(struct point));   //创建一个新点
        p_p->next = NULL;                                                   //这个点的下一个步尚且未知
        p_p->x = c_p_p->x;                                                //新点的x坐标：当前点的坐标+1
        p_p->y = (c_p_p->y)+1;                                                    //新店的Y坐标：不变
        c_p_p->next = p_p;                                                  //链表串起来
        c_p_p = p_p;                                                        //新的当前位置
        
    }



}

void go_down(int steps){
    int i;
    for(i=0;i<steps;i++)
    {
        struct point *p_p = (struct point *)malloc(sizeof(struct point));   //创建一个新点
        p_p->next = NULL;                                                   //这个点的下一个步尚且未知
        p_p->x = c_p_p->x;                                                //新点的x坐标：当前点的坐标+1
        p_p->y = (c_p_p->y)-1;                                                    //新店的Y坐标：不变
        c_p_p->next = p_p;                                                  //链表串起来
        c_p_p = p_p;                                                        //新的当前位置
    }


}


void destory_all(){

}
