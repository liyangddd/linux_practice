#include "client.h"
#define FIFO_NAME "my_fifo"
int main() {
  int pipe_fd;
  int res;
  int open_mode = O_RDONLY;
  char buf[1024] = "1234abcd";

  if (access(FIFO_NAME, F_OK) == -1) {
    res = mkfifo(FIFO_NAME, 0777);
    if (res != 0) {
      fprintf(stderr, "Could not creare fifo %s\n", FIFO_NAME);
      exit(EXIT_FAILURE);
    }
  }

  pipe_fd = open(FIFO_NAME, open_mode);
/*
  if (pipe_fd != -1) {
    write(pipe_fd, buf, 1024);
  }
  else {
    exit(EXIT_FAILURE);
  }
*/
  sleep(5);
 
 char buf2[1024];
  memset(buf2, '\0', sizeof(buf));
  read(pipe_fd, buf2, 1024);
  printf("______: %s\n", buf);
  return 0;
}
