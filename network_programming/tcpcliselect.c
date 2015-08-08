#include "myheader.h"

void str_cli(FILE *fp, int sockfd)
{
  //stdineof是一个初始化为0的标志，只要该标志为0，每次在主循环中总是
  //select标准输入的可读性
   int maxfdp1, stdineof;
   fd_set rset;
   char buf[MAXLINE];
   int n;

   stdineof = 0;
   FD_ZERO(&rset);
   for ( ; ; ) {
      if (stdineof == 0)
	FD_SET(fileno(fp), &rset);
      FD_SET(sockfd, &rset);
      maxfdp1 = (fileno(fp) > sockfd ? fileno(fp) : sockfd) + 1;
      Select(maxfdp1, &rset, NULL, NULL, NULL);
      
      //当在套接字上读到EOF时，如果我们已经在标准输入上遇到EOF,那就是正常
      //终止，函数返回。但是如果还没有在标准输入遇到EOF，那么服务器进程已经
      //过早终止。只有服务器进程终止，select就会立刻通知客户端进程。
      if (FD_ISSET(sockfd, &rset)) { //socket可读
	if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
	  if (stdineof == 1)
	    return;
	  else
	    err_quit("str_cli: server terminated prematurely");
	}
	Write(fileno(stdout), buf, n);
      }
      
      //当在标准输入遇到EOF，把标志stdineof设为1，
      //并把第二个参数设置为SHUT_WR来调用shutdown以发送FIN。
      if (FD_ISSET(fileno(fp), &rset)) { //stdout可读
	if ((n = Read(fileno(fp), buf, MAXLINE)) == 0) {
	   stdineof = 1;
	   Shutdown(sockfd, SHUT_WR);
	   FD_CLR(fileno(fp), &rset);
	   continue;
	}
	Writen(sockfd, buf, n);
      }
   }
}

int main(int argc, char **argv)
{
   int sockfd;
   struct sockaddr_in servaddr;
   if (argc != 2)
      err_quit("usage: tcpcliselect <IP address>\n");
   sockfd = Socket(AF_INET, SOCK_STREAM, 0);
   
   memset(&servaddr, 0, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(SERV_PORT);
   Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

   Connect(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr));
   
   str_cli(stdin, sockfd);
  
   exit(0);
}
