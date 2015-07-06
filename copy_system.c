#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
  char c;
  int in, out;
  
  in = open("second2", O_RDONLY);
  out = open("file.out", O_WRONLY | O_CREAT, 0777);
  while (read(in, &c, 1)) {
    write(out, &c, 1);
  }
  return 0;
}