```
#include <stdio.h>
#include <unistd.h>

int bubble_sort_1(void *src,long size);
int bubble_sort_2(void *src,long size);
int bubble_max(void,long size,long *max);

int main(int argc,char **argv)
{
    long max;
    long size,i;
    long a[]={1,2,3,1235,8873,111,1112,23,99,47,9627,56,1,13,2,3,985,'a','3'};

    /*求最大值*/
    //bubble_max(a,sizeof(a)/sizeof(long),&max);
    //printf(“[bubble max] max = %ld\n”,max);

    /*单向排序*/
    //bubble_sort_1(a,sizeof(a)/sizeof(long));
  
    /*双向排序*/
    bubble_sort_2(a,sizeof(a)/sizeof(long));
  
    printf("[bubble sort]:");
    for(i=0;i<sizeof(a)/sizeof(long);i++)
    {
      printf("%ld,",a[i]);
    }
    fflush(stdout);
    while(1)
    {
      sleep(1);
    }  
}

/*单向冒泡*/
int bubble_sort_1(void *src,long size)
{
    long *p;
    long *q;
    p=src;
    q=src;
    long exchange;
    long i,j,tmp;
  
    for(j=0;j<size-1;j++)
    {
        p=src;
        for(i=0;i<size-1;i++)
        {
            if(*p>*(p+1))
            {
                exchange=*(p+1);
                *(p+1)=*p;
                *p=exchange;
            }
            p++;
        }
  
        for(tmp=0;tmp<size;tmp++)
        {
            printf("%ld,",q[tmp]);
        }
        printf("\n");
    }
    return 0;
}

/*双向冒泡*/
int bubble_sort_2(void *src,long size)
{
    long *p;
    long *q;
    p=src;
  
    long exchange;
    long i,j,k,tmp;
    
    for(i=0;i<size-1;i++)
    {
        if(*p>*(p+1))
        {
            exchange=*(p+1);
            *(p+1)=*p;
            *p=exchange;
            //反向冒泡
            q=p;
            for(k=i;k>0;k--)
            {
                if(*q<*(q-1))
                  {
                      exchange=*(q-1);
                      *(q-1)=*q;
                      *q=exchange;
                  }
                q--;
             }
         }
         p++;
     }
    return 0;
}

/*冒泡法求最大值*/
int bubble_max(void *src,long size,long *max)
{
    long exchange;
    long i;
    long *q;
    
    q=src;
    
    if(src==NULL)
    {
        printf("null array");
        return -1;
    }

    for(i=0;i<size-1;i++)
    {
        if(*q>*(q+1))
            {
                exchange=*(q+1);
                *(q+1)=*q;
                *q=exchange;
            }
        q++;
    }
    *max=*q;
    return 0;
}
```







