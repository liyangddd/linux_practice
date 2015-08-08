#include "myheader.h"

int main(int argc, char **argv) {
  int sockfd, n;
  char recvline[MAXLINE + 1];
  struct sockaddr_in servaddr;
  struct in_addr **pptr;
  struct in_addr *inetaddrp[2];
  struct in_addr inetaddr;
  struct hostent *hp;
  struct servent *sp;
  
  if (argc != 3)
    err_exit("usage: daytimetcpcli1 <hostname> <service>");
  
  if ((hp = gethostbyname(argv[1])) == NULL) {
    if (inet_aton(argv[1], &inetaddr) == 0)
      err_exit("hostname error");
    else {
      inetaddrp[0] = &inetaddr;
      inetaddrp[1] = NULL;
      pptr = inetaddrp;
    }
  }
  else
    pptr = (struct in_addr **)hp->h_addr_list;
  
  if ((sp = getservbyname(argv[2], "tcp")) == NULL)
    err_exit("getservbyname error");
  
  for (; *pptr != NULL; pptr++) {
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = sp->s_port;
    memcpy(&servaddr.sin_addr, *pptr, sizeof(struct in_addr));
    static char str[128];
    printf("trying %s\n", Inet_ntop(AF_INET, &servaddr.sin_addr, str,
sizeof(str)));
    
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == 0) {
      break;
    }
    err_exit("connect error");
    close(sockfd);
  }
  if (*pptr == NULL)
    err_exit("unable to connect");
  
  while ((n = Read(sockfd, recvline, MAXLINE)) > 0) {
    recvline[n] = 0;
    Fputs(recvline, stdout);
  }
  exit(0);
} 