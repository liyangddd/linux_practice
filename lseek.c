#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
  int in = open("lseek.txt", O_RDWR | O_CREAT);
  char buf1[] = "abcdefghij";
  char buf2[] = "ABCDEFGHIJ";
  char buf3[] = "UUU";
  if (in < 0) {
    printf("open file error.");
  }
  if (write(in, buf1, 10) != 10) {
    printf("write file error");
  }
  if (lseek(in, 200, SEEK_SET) == -1) {
    printf("lseek error.");
  } 
  if (write(in, buf2, sizeof(buf2)) < 0) {
     printf("write buf2 in file error.");
  }
  if (lseek(in, 2, SEEK_SET) == -1) {
    printf("lseek error.");
  }
  if (write(in, buf3, sizeof(buf3)) < 0) {
     printf("write buf2 in file error.");
  }
  exit(0);
}