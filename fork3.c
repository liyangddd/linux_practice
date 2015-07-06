#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int glob = 6;
char buf[] = "a write to stdout\n";
int main() {
  char buf1[] = "ABCDE";
  char buf2[] = "cdefg";
  int var;
  pid_t pid;
  FILE *fd;
  fd = fopen("temp.txt", "a+");
  if (!fd) {
    perror("open file temp.txt error\n");
  }
  
  var = 88;
  if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
    perror("write error");
  printf("before fork\n");
  
  if ((pid = fork()) < 0) {
    perror("fork error");
  }
  else if (pid == 0) {
    glob++;
    var++;
    for (int i = 0; i< 5; i++) {
    fputs(buf1, fd);
    }
  }
  else {
    for (int i = 0; i < 5; i++) {
      fseek(fd, i, SEEK_SET);
      fputs(buf2, fd);
    }
    sleep(2);
  }
  printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
  exit(0);
}