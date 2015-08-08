#include "myheader.h"

int main(int argc, char **argv)
{
  int i, maxi, maxfd, listenfd, connfd, sockfd;
  int nready, client[FD_SETSIZE];
  ssize_t n;
  fd_set rset, allset;
  char buf[MAXLINE], cliip[MAXLINE];
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr;
  
  listenfd = Socket(AF_INET, SOCK_STREAM, 0);
  
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);
  
  Bind(listenfd, (const struct sockaddr*)&servaddr, sizeof(servaddr));
  
  Listen(listenfd, LISTENQ);
  
  maxfd = listenfd;
  maxi = -1;
  for (i = 0; i < FD_SETSIZE; i++)
    client[i] = -1;
  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);
  
  for ( ; ; ) {
    //select等待某事件发生：或是新客户连接建立，或是数据、FIN或RST到达
    rset = allset;
    nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
    
    //如果某个监听套接字可读，那么建立一个新连接。
    //调用accept并相应更新数据结构，使用client数组中
    //第一个未用记录这个已连接描述符。就绪描述符数目减1，若其值为0，
    //就可以避免进入下一个for循环。这样做让我们可以使用select的返回值
    //来避免检查未就绪的描述符
    if (FD_ISSET(listenfd, &rset)) {
      clilen = sizeof(cliaddr);
      connfd = Accept(listenfd, (const struct sockaddr*)&cliaddr, &clilen);
      printf("new client: %s, port %d \n",
	    Inet_ntop(AF_INET, &cliaddr.sin_addr, cliip, sizeof(buf)),
             ntohs(cliaddr.sin_port));
	     
      for (i = 0; i < FD_SETSIZE; i++)
	if (client[i] < 0) {
	  client[i] = connfd;
	  break;
	}
      if (i == FD_SETSIZE)
	err_quit("too many clients");
      
      FD_SET(connfd, &allset);
      if (connfd > maxfd)
	maxfd = connfd;
      if (i > maxi)
	maxi = i;
      
      if (--nready <= 0)
	continue;
    }
    
   //对于每个现有的客户连接，要测试其描述符是否在select返回的描述符集中。
   //如果是就从该客户读入一行文本并回射给它。如果该客户已经关闭连接，read
   //返回0，更新数据结构。
    for (i = 0; i <= maxi; i++) {
      if ((sockfd = client[i]) < 0)
	continue;
      if (FD_ISSET(sockfd, &rset)) {
        if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
	  Close(sockfd);
	  FD_CLR(sockfd, &allset);
	  client[i] = -1;
	}
	else
	  Writen(sockfd, buf, n);
	
	if (--nready <= 0)
	  break;
      }
    }
  }
}