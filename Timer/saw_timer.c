#include <linux/timer.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static inline void Start_timer(struct timer_list *timer,unsigned long msec);
static inline void Init_timer(struct timer_list *timer,Handler routine,unsigned long argument);
static inline void Cancle_timer(struct timer_list *timer);

typedef void (*Handler) (void *);

struct timer_class{
        struct timer_list identity;
        char * desc;
        unsigned long interval;

        Handler routine;
}timer1;


int main (int argc,char ** argv)
{
        timer1.desc="timer used for xxx\n";
        timer1.interval=1000;
        timer1.routine=(Handler)time_out_handler;

        //1.INIT A TIMER
        Init_timer(&(timer1.identity),timer1.routine,(unsigned long)timer1);
        //2.START A TIMER
        Start_timer(&(timer1.identity),timer1.interval);
        //3.have a sleep
        while(1) sleep(1);
}

void time_out_handler(struct timer_class *argu)
{
        arug=(struct timer_calss *)argu;
        //restart timer
        Start_timer(argu->interval);
        argu->interval *=2;
//      printf("time out! timer set to %ld\n",argu->interval);
}


static inline void Start_timer(struct timer_list *timer,unsigned long msec)
{
        mod_timer(timer,jiffies + msec_to_jiffies(msec) + 1);
}

static inline void Init_timer(struct timer_list *timer,Handler routine,unsigned long argument)
{
        setup_timer(timer,routine,argument);
}

static inline void Cancle_timer(struct timer_list *timer)
{
        del_timer_sync(timer);
}
~
