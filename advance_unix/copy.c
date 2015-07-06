#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#define BUF_SIZE 4096
#define FILE_IN  "/home/yang/libnids-1.24/weibo/test1.pcap"

int main() {
  time_t t1 = time((time_t *)NULL);
  printf("ssss  %d\n", t1);

/*
  int fd = open(FILE_IN, O_RDONLY);
  if (fd < 0) {
    perror("open file read error");
    exit(-1);
  }
  int fd2 = open("test.pcap", O_RDWR | O_CREAT);
  if (fd2 < 0) {
    perror("open file write error");
    exit(-1);
  }

  int nread;
  char buf[BUF_SIZE];
  while ((nread = read(fd, buf, BUF_SIZE)) > 0) {
    if (write(fd2, buf, nread) != nread) {
        perror("write error");
        exit(-1);
    }
  }
  
  if (nread < 0) {
    perror("read error");
    exit(-1);
  }
  close(fd2);
  close(fd);
*/

  void *src, *dst;
  int fdin = open(FILE_IN, O_RDONLY);
  if (fdin < 0) {
    perror("open file read error");
    exit(-1);
  }
  int fdout = open("test.pcap", O_RDWR | O_CREAT);
  if (fdout < 0) {
    perror("open file write error");
    exit(-1);
  }  
  
  struct stat statbuf;
  if (fstat(fdin, &statbuf) < 0) {
    perror("fstat error");
    exit(-1);
  }
  if (lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1)  {
    perror("lseek error");
    exit(-1);
  }
  if (write(fdout, "", 1) != 1)  {
    perror("write error");
    exit(-1);
  }

  if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)  {
    perror("mmap in error");
    exit(-1);
  }
  if ((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED)  {
    perror("mmap write error");
    exit(-1);
  }
  memcpy(dst, src, statbuf.st_size);
  time_t t2 = time((time_t *)NULL);
  printf("sssdd  %d\n", t2);
  printf("%d\n", t2 - t1);
  munmap(src, statbuf.st_size);
  munmap(dst, statbuf.st_size);
  return 0;
}
