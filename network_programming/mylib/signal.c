#include "../myheader.h"

Sigfunc *
Signal(int signo, Sigfunc *func)
{
   struct sigaction act, oact;
   act.sa_handler = func;
   sigemptyset(&act.sa_mask);
   act.sa_flags = 0;
   if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
      act.sa_flags |= SA_INTERRUPT;
#endif
   }
   else {
#ifdef SA_RESTART
      act.sa_flags |= SA_RESTART;
#endif
   }
   if (sigaction(signo, &act, &oact) < 0)
      return(SIG_ERR);
   return(oact.sa_handler);
}

void onSignalCatch(int signalNumber)
{
    pid_t pid;
    int stat;
    //pid = wait(&stat);
    //下列函数的第一个参数为－1表示等待第一个终止的子进程
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) 
      printf("child %d terminated.\n", pid);
    return;
 }
