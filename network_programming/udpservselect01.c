#include "myheader.h"

void str_echo(int sockfd) {
   ssize_t n;
   char buf[MAXLINE];
again:
   while (( n = read(sockfd, buf, MAXLINE)) > 0)
      Writen(sockfd, buf, n);
   if (n < 0 && errno == EINTR)
      goto again;
   else if (n < 0) {
      err_exit("str_echo: read error.");   
   }
}

int main(int argc, char **argv)
{
  int listenfd, connfd, udpfd, nready, maxfdp1;
  char mesg[MAXLINE];
  pid_t childpid;
  fd_set rset;
  ssize_t n;
  socklen_t len;
  const int on = 1;
  struct sockaddr_in cliaddr, servaddr;
  void onSignalCatch(int);
  
  struct hostent *hptr;
  struct sockaddr_in testaddr;
  Inet_pton(AF_INET, argv[1], &testaddr.sin_addr);
  hptr = gethostbyaddr((char*)&testaddr.sin_addr, sizeof(testaddr.sin_addr),
AF_INET);
  printf("offical hostname: %s\n", hptr->h_name);
  char **pptr;
  for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
    printf("\t alias: %s\n", *pptr);
  listenfd = Socket(AF_INET, SOCK_STREAM, 0);
  
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);
  
  //设置SO_REUSEADDR套接字以防该端口上已经有连接
  Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
  Listen(listenfd, LISTENQ);
  
  //以下创建UDP套接字并绑定与TCP套接字相同的端口。这里无须设置SO_REUSEADDR
  //因为TCP端口独立于UDP端口
  udpfd = Socket(AF_INET, SOCK_DGRAM, 0);
  
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);
  Bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
  
  //处理SIGCHLD信号，因为TCP连接由子进程处理
  Signal(SIGCHLD, onSignalCatch);
  
  FD_ZERO(&rset);
  //计算等待的描述符中较大的
  int maxfd = listenfd > udpfd ? listenfd : udpfd;
  maxfdp1 = maxfd + 1;
  
  for( ; ; ) {
    //调用select等待监听TCP或UDP套接字变为可读
    FD_SET(listenfd, &rset);
    FD_SET(udpfd, &rset);
    if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
      //信号处理函数可能中断对select的调用，因此要处理EINTR错误
      if (errno == EINTR)
	continue;
      else
	err_exit("select error\n");
    }
    
    if (FD_ISSET(udpfd, &rset)) {
      len = sizeof(cliaddr);
      n = Recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr*)&cliaddr, &len);
      Sendto(udpfd, mesg, n, 0, (struct sockaddr*)&cliaddr, len);
    }
    
    if (FD_ISSET(listenfd, &rset)) {
      len = sizeof(cliaddr);
      connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &len);
      if ((childpid = Fork()) == 0) { //child process
        Close(listenfd);   //close listening socket
	str_echo(connfd);  //process the request
	exit(0);
      }
      Close(connfd);  //parent closes connected socket
    }
  }
}