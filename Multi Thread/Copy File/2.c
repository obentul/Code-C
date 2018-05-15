/*使用： ./2 源文件 目标文件 线程数
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>



int fd_src;
int fd_des;
pthread_mutex_t flag; //资源锁，拿锁者有写权限



void cp(void)
{
    int cnt =0;
    char buff[10];
    memset(buff,0x00,10);

    while(1)
    {
        pthread_mutex_lock(&flag);
        cnt = read(fd_src,buff,10);
        if(cnt==0)
            {
                pthread_mutex_unlock(&flag);
                break;
            }
        write(fd_des,buff,cnt);
        pthread_mutex_unlock(&flag);
    }
    pthread_exit(0);
}



void do_job(int thread_num)
{
    pthread_t tid[thread_num];
    while(thread_num--)
    {
        pthread_create(&tid[thread_num],NULL,(void *)cp,NULL);
    }
    sleep(5); //等待子线程执行完
}



int main(int argc,char ** argv)
{
    char * src_path=NULL;
    char * des_path=NULL;
    int thread_num=0;

    pthread_mutex_init(&flag,NULL);

    if(argc!=4)
    {
        printf("argu num must be 4\n");
        return -1;
    }

    thread_num = atoi(argv[3]);
    src_path=(char *)malloc(sizeof(argv[1]));
    des_path=(char *)malloc(sizeof(argv[2]));
    memcpy(src_path,argv[1],sizeof(argv[1]));
    memcpy(des_path,argv[2],sizeof(argv[2]));

    printf("copy file %s to %s \n",src_path,des_path);
    
    fd_src = open(src_path,O_RDONLY);
    if(fd_src== -1)
        {
            perror("open src file error\n");
            return -1;
        }

    fd_des = open(des_path,O_RDWR|O_CREAT);
    if(fd_des == -1)
        {
            perror("open des file error\n");
            return -1;
        }

    do_job(thread_num);
    pthread_mutex_destory(&flag);
    return 0;
}
