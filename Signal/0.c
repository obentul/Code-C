#include <stdio.h>
#include <signal.h>

void HANDLER(int signo)
{
	printf("xxxxx\n");
}

int main(int argc,char ** argv)
{
	signal(SIGUSR1,HANDLER);

	sigset_t s1,s2;
	sigemptyset(&s1);
	sigaddset(&s1,SIGUSR1);

	//sigprocmask(SIG_BLOCK,&s1,&s2);  //有这行，就不进入HANDLER;无，则可进

	while(1) sleep(1);

}
