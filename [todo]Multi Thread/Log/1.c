/* LOG_BUFF_SIZE尺寸必须足够大，不然缓冲区一满就会刷入文件中，这样日志就会很乱
 * LOG_BUFF_SIZE一定要大于一次业务的日志量
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


#define LOG_BUFF_SIZE 8192



void* job(void)
{
	FILE *log_p;
	char LOG_BUFF[LOG_BUFF_SIZE];
	char ch='A';
	int j,k;

	log_p=fopen("./1.log","a+");
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
}


int main(int argc,char ** argv)
{
	int n;
	int tid[20];

	if(argc!=2)
	{
		exit(-1);
	}

	n=atoi(argv[1]);

	while(n--)
	{
		pthread_create(&tid[n],NULL,job,NULL);
	}
	while(1) sleep(1);
}















