#include "mythread.h"

int lock_read(int fd,void *buf,size_t count,pthread_mutex_t *mutex)
{
        int n,i=0;

        again:
        if(pthread_mutex_trylock(&mutex)!=0)
        {
                if(errno==EBUSY)
                goto again;
                else
                {
                        perror("trylock error");
                        return -1;
                }
        }

        again1:
        n=read(fd,buf,count);
        if((n!=0)&&(n!=-1))
        {
                i=i+n;
                goto again1;
        }
        else if(n==0)
        {
                printf("read done\n");
        }
        else
        {
                pthread_mutex_unlock(&mutex);
                perror("read error");
                return -1;
        }

        pthread_mutex_unlock(&mutex);

        return 0;
}

int lock_write(int fd,void *buf,size_t count,pthread_mutex_t *mutex)
{
        int n,i=0;

        again:
        if(pthread_mutex_trylock(&mutex)!=0)
        {
                if(errno==EBUSY)
                goto again;
                else
                {
                        perror("trylock error");
                        return -1;
                }
        }

        again1:
        n=write(fd,buf,count);
        if((n!=0)&&(n!=-1))
        {
                i=i+n;
                goto again1;
        }
        else if(n==0)
        {
                printf("write done\n");
        }
        else
        {
                pthread_mutex_unlock(&mutex);
                perror("write error");
                return -1;
        }

        pthread_mutex_unlock(&mutex);

        return 0;

}
