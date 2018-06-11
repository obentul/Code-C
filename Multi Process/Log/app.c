#include <stdio.h>

#define LOG_PATH "./1.log"
#define LOG_BUFF_SIZE 8192

char LOG_BUFF[LOG_BUFF_SIZE];

int main(int argc,char ** argv)
{
    FILE *log_p;
    //char buff[8192];
    char ch='A';
    int j,k;


    log_p = fopen(LOG_PATH,"a+");
    setvbuf(log_p,LOG_BUFF,_IOFBF,LOG_BUFF_SIZE);

    while(1)
    {
        memset(LOG_BUFF,0x00,LOG_BUFF_SIZE);
        fprintf(log_p,"=========================start   [%d]===========================\n",getpid());

        for(j=0;j<20;j++)
        {
             fprintf(log_p,"[%s][%d][%d]",__FILE__,__LINE__,getpid());
             for(k=0;k<100;k++)
             {
                 fprintf(log_p,"%c",ch);
             }
             fprintf(log_p,"\n");
             ch++;
        }

        fprintf(log_p,"+++++++++++++++++++++++++end     [%d]+++++++++++++++++++++++++++\n",getpid());
        ch='A';
        fflush(log_p);
        sleep(1);
    }

    fclose(log_p);
}
