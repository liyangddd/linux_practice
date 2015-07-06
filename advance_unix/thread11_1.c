#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_t ntid;
void printids(const char *s) {
  pid_t pid;
  pthread_t tid;

  pid = getpid();
  tid = pthread_self();
  printf("%s pid %u tid %u (%x)\n", s, (unsigned int)pid,
         (unsigned int)tid, (unsigned int)tid);
}
void *thr_fn2(void *arg) {
  printids("new new thread: ");
}

void *thr_fn(void *arg) {
  printids("new thread: ");
  int err;
  err = pthread_create(&ntid, NULL, thr_fn2, NULL);
  if (err != 0) {
    printf("can not create thread in: %s\n", strerror(err));
    return (void *)0;
  }
  sleep(1);
  return ((void*)0);
}

int main() {
  int err;
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  if (err != 0) {
     printf("can not create thread: %s\n", strerror(err));
     return -1;
  }
  printids("main thread: " );
  sleep(1);
  exit(0);
}
