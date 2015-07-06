#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  char block[1024];
  FILE *in, *out;
  int c;
  int nread;
  
  in = fopen("second2", "r");
  out = fopen("test.txt", "w");
  printf("%d %d %d\n", ferror(out), getuid(), getgid());
  while (fgets(block, 4, in) != NULL) {
    fputs(block, out);
     //printf("%s\n", block);
  }
  chown("test.txt", 3330, 33);
  chmod("test.txt", S_IRWXU | S_IRGRP | S_IXGRP);
//   in = open("second2", O_RDONLY);
//   int in2 = dup(in);
//   printf("filedes: %d, %d\n", in2, in);
//   out = open(in2, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
//   while ((nread = read(in, block, sizeof(block))) > 0) {
//     write(out, block, nread);
//     write(1, block, nread);
//   }
//   return 0;
}