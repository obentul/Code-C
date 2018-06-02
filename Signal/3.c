//描述：把信号SIGINT设置为轮询sigpending
//
//
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

sigset st;

void SIGINT_HANDLER(int signo)
{
	sigpending(&st);
	sigpro	

}

int main(int argc, char ** argv)
{
	struct sigaction sa1,sa2;
	memset(&sa1,0x00,sizeof(struct sigaction));

	sa1.sa_handler=


}
