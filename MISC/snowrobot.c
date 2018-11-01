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

#define XX 11
#define YY 12
#define LOCATE(y,x) (x*YY+y)

char map[XX*YY]={};
char BUFFER[2048];



void init_map();
void disp_map();
int check();
void go_left(int steps);
void go_right(int steps);
void go_up(int steps);
void go_down(int steps);




void control_func(void)
{
    char direction;
    while(1)
    {
        scanf("%c",&direction);
        fflush(stdin);
        switch(direction)
        {
            case 'd':go_right(1); break;
            case 'a':go_left(1); break;
            case 'w':go_up(1); break;
            case 's':go_down(1); break;
        }
    }
}


int main(int argc,char **argv)
{
    pthread_t tid;
    memset(map,'0',sizeof(map));
    start_point.x=0;
    start_point.y=0;
    start_point.next=NULL;
    c_p_p = &start_point;
    setvbuf(stdout,BUFFER,_IOFBF,2048);
    //初始值
    init_map();

    printf("%c\n",map[LOCATE(5,5)]);
    sleep(1);

    pthread_create(&tid,NULL,(void *)&control_func,NULL);

    while(1)
    {
        //每1秒输出依次map里的内容
        disp_map();
        sleep(1);
        system("clear");
    }


    destory_all();
}

void init_map(){
     int i=0;

     map[(11-1)/2*12+(11-1)/2]='-'; //中间点位置
     for(i=0;i<11;i++)
     {
        map[11*(i+1)+i]='\n';   //每行的最后一个字节
     }
}

void disp_map(){
    write(1,map,11*12);
    fflush(stdout);
}

int locate_map(struct point *tmp){
    int x1=tmp->x-(XX-1)/2;      //x1是数组坐标系的x
    int y1=tmp->y+(YY-1)/2;       //y1是数组坐标系的y
    char show=tmp->show;    
    
    char locate = LOCATE(x1,y1);

    map[locate]=show;

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
    struct point *p_p;
    for(i=0;i<steps;i++)
    {
        p_p = (struct point *)malloc(sizeof(struct point));   //创建一个新点
        p_p->next = NULL;                                                   //这个点的下一个步尚且未知
        p_p->x = (c_p_p->x)-1;                                                //新点的x坐标：当前点的坐标-1
        p_p->y = c_p_p->y;                                                    //新店的Y坐标：不变
        p_p->show = '<';
        c_p_p->next = p_p;                                                  //链表串起来
        c_p_p = p_p;                                                        //新的当前位置
    }
    locate_map(p_p);
}
void go_right(int steps){
    int i;
    struct point *p_p;
    for(i=0;i<steps;i++)
    {
        p_p = (struct point *)malloc(sizeof(struct point));   //创建一个新点
        p_p->next = NULL;                                                   //这个点的下一个步尚且未知
        p_p->x = (c_p_p->x)+1;                                                //新点的x坐标：当前点的坐标+1
        p_p->y = c_p_p->y;                                                    //新店的Y坐标：不变
        p_p->show = '>';
        c_p_p->next = p_p;                                                  //链表串起来
        c_p_p = p_p;                                                        //新的当前位置
    }
    locate_map(p_p);
}

void go_up(int steps){
    int i;
    struct point *p_p;
    for(i=0;i<steps;i++)
    {
        p_p = (struct point *)malloc(sizeof(struct point));   //创建一个新点
        p_p->next = NULL;                                                   //这个点的下一个步尚且未知
        p_p->x = c_p_p->x;                                                //新点的x坐标：当前点的坐标+1
        p_p->y = (c_p_p->y)+1;                                                    //新店的Y坐标：不变
        p_p->show = '/';
        c_p_p->next = p_p;                                                  //链表串起来
        c_p_p = p_p;                                                        //新的当前位置
        
    }
    locate_map(p_p);
}

void go_down(int steps){
    int i;
    struct point *p_p;
    for(i=0;i<steps;i++)
    {
        p_p = (struct point *)malloc(sizeof(struct point));   //创建一个新点
        p_p->next = NULL;                                                   //这个点的下一个步尚且未知
        p_p->x = c_p_p->x;                                                //新点的x坐标：当前点的坐标+1
        p_p->y = (c_p_p->y)-1;                                                    //新店的Y坐标：不变
        p_p->show = '\\';
        c_p_p->next = p_p;                                                  //链表串起来
        c_p_p = p_p;                                                        //新的当前位置
    }
    locate_map(p_p);
}


void destory_all(){

}
