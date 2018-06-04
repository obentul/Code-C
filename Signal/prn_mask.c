#include <stdio.h>
#include <signal.h>

int prn_mask(void)
{
	sigset_t st;
	sigprocmask(0,NULL,&st);
	printf("++++++++++");
	 if(sigismember(&st,SIGHUP))	printf("SIGHUP SET\n");
	 if(sigismember(&st,SIGINT))     printf("SIGINT SET\n");
         if(sigismember(&st,SIGQUIT))     printf("SIGQUIT SET\n");
         if(sigismember(&st,SIGILL))     printf("SIGILL SET\n");
         if(sigismember(&st,SIGTRAP))     printf("SIGTRAP SET\n");
         if(sigismember(&st,SIGABRT))     printf("SIGABRT SET\n");
         if(sigismember(&st,SIGFPE))     printf("SIGFPE SET\n");
         if(sigismember(&st,SIGKILL))     printf("SIGKILL SET\n");
         if(sigismember(&st,SIGUSR1))     printf("SIGUSR1 SET\n");
         if(sigismember(&st,SIGSEGV))     printf("SIGSEGV SET\n");
         if(sigismember(&st,SIGUSR2))     printf("SIGHUSR2 SET\n");
         if(sigismember(&st,SIGPIPE))     printf("SIGPIPE SET\n");
         if(sigismember(&st,SIGALRM))     printf("SIGALRM SET\n");
         if(sigismember(&st,SIGTERM))     printf("SIGTERM SET\n");
         if(sigismember(&st,SIGCHLD))     printf("SIGCHLD SET\n");
         if(sigismember(&st,SIGCONT))     printf("SIGCONT SET\n");
         if(sigismember(&st,SIGSTOP))     printf("SIGSTOP SET\n");
         if(sigismember(&st,SIGTSTP))     printf("SIGTSTP SET\n");
         if(sigismember(&st,SIGTTIN))     printf("SIGTTIN SET\n");
         if(sigismember(&st,SIGTTOU))     printf("SIGTTOU SET\n");
	printf("-----------");
}
