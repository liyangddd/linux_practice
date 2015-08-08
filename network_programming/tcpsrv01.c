#include "myheader.h"

//extern void onSignalCatch(int);

void str_echo(int sockfd) {
   ssize_t n;
   char buf[1024];
again:
   while (( n = read(sockfd, buf, 1024)) > 0)
      write(sockfd, buf, n);
   if (n < 0 && errno == EINTR)
      goto again;
   else if (n < 0) {
      err_exit("str_echo: read error.");   
   }
}

int main(int argc, char **argv) {
   int listenfd, connfd;
   pid_t childpid;
   socklen_t clilen;
   struct sockaddr_in cliaddr, servaddr;
   listenfd = socket(AF_INET, SOCK_STREAM, 0);
   if (listenfd == -1) {
      err_exit("socket error: tcp server.");
   } 

   memset(&servaddr, 0, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(9877);

   if (bind(listenfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
      err_exit("bind error.");
   if (listen(listenfd, 1024) == -1)
      err_exit("listen eror");

   Signal(SIGCHLD, onSignalCatch);//onSignalCatch

   for(; ; ) {
      clilen = sizeof(cliaddr);
      if ((connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen)) < 0) {
          if (errno == EINTR)
             continue;  //有些系统不会重启被这中断的系统调用，所以要处理被中断的系统调用
          else
             err_exit("accept error, server.\n");
      }
      if ((childpid = fork()) == 0) {
         close(listenfd);
         str_echo(connfd);
         exit(0);
      }
      close(connfd);
   }
}

