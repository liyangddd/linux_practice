#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
  int fd = open("open_test1", O_RDWR | O_CREAT);
  printf("%d\n", fd);
//   char buffer[128];
//   int nread;
//   
//   nread = read(0, buffer, 128);
//   if (nread == -1) {
//     write(2, "A read error has occurred\n", 26);
//   }
//   
//   if ((write(1, buffer, nread)) != nread)
//     write(2, "a write error has occurred\n", 27);
//   
//   exit(0);
   return 0;
}