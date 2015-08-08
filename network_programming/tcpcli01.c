#include "myheader.h"

void str_cli(FILE *fp, int sockfd) {
   char sendline[1024], recvline[1024];
   while (fgets(sendline, 1024, fp) != NULL) {
      write(sockfd, sendline, strlen(sendline));
      if (read(sockfd, recvline, 1024) == 0) {
         err_exit("str_cli: server terminated prematurely");
      }
      fputs(recvline, stdout);
   }
}

int main(int argc, char **argv) {
   int sockfd;
   struct sockaddr_in servaddr;
   if (argc != 2)
      err_quit("usage: tcpcli <IPaddress>\n");
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   int   sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
   memset(&servaddr, 0, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(9877);
   inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
   if (connect(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
      err_exit("connnet error");

   
   if (connect(sockfd2, (const struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
   err_exit("connnet error");
   str_cli(stdin, sockfd);
   exit(0);
}
