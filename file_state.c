#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  struct stat statbuf;
  mode_t modes;
  stat("file.out", &statbuf);
  modes = statbuf.st_mode;
  printf("%c\n", modes);
}