#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv[]) {
  char *filename;
  if (argc != 2) {
    fprintf(stderr, "usage: usetoupper file\n");
    exit(1);
  }
  
  filename = argv[1];
  if (!freopen(filename, "r", stdin)) {
    fprintf(stderr, "could not redirect stdin from file %s\n", filename);
    exit(2);
  }
  execl("./a.out", "", 0);
  exit(3);
}