#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 10240

int main() {
  FILE *write_fp;
  char buffer[BUFSIZE + 1];
  sprintf(buffer, "One upon a time, \\there was...\n");
  write_fp = popen("od -x", "w");
  if (write_fp != NULL) {
    fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
    pclose(write_fp);
    exit(EXIT_SUCCESS);
  }
  exit(EXIT_FAILURE);
}
