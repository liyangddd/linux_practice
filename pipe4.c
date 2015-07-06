#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1024

int main(int argc, char *argv[]) {
  int data_processed;
  char buffer[BUFSIZE + 1];
  int file_descriptor;
  
  memset(buffer, '\0', sizeof(buffer));
  sscanf(argv[1], "%d", &file_descriptor);
  data_processed = read(file_descriptor, buffer, BUFSIZE);
  
  printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
  exit(EXIT_SUCCESS);
}