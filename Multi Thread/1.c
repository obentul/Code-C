#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void hello(void)
{
  printf("hello\n");
}

int main(int argc,char ** argv)
{
  pthread_t ptid;
  pthread_create(&ptid,NULL,(void *)hello,NULL);
  sleep(1);
  return 0;
}
