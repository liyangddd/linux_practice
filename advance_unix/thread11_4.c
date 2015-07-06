#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void cleanup(void *arg) {
  printf("cleanup: %s\n", (char*)arg);
}

void *thr_fn1(void *arg) {
  printf("thread 1 start\n");
  pthread_cleanup_push(cleanup, "1 first handler");
  pthread_cleanup_push(cleanup, "1 second handler");
  printf("1 push complete\n");
  if (arg)
    return ((void*)1);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  return ((void*)1);
}

void *thr_fn2(void *arg) {
  printf("thread 2 start\n");
  pthread_cleanup_push(cleanup, "2first handler");
  pthread_cleanup_push(cleanup, "2 second handler");
  printf("2 push complete\n");
  if (arg)
    return ((void*)2);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  return ((void*)2);
}

int main() {
  int err;
  pthread_t tid1, tid2;
  void *tret;
  
  err = pthread_create(&tid1, NULL, thr_fn1, (void*)1);
  if (err != 0) {
     printf("can not create thread1: %s", strerror(err));
     exit(-1);
  }

  err = pthread_create(&tid2, NULL, thr_fn2, (void*)1);
  if (err != 0) {
     printf("can not create thread2: %s", strerror(err));
     exit(-1);
  }

  err = pthread_join(tid1, &tret);
  if (err != 0) {
    printf("can not join with thread 1: %s\n", strerror(err));
     exit(-1);
  }
  printf("1 exit code: %d\n", (int)tret);

  err = pthread_join(tid2, &tret);
  if (err != 0) {
    printf("can not join with thread 2: %s\n", strerror(err));
     exit(-1);
  }
  printf("2 exit code: %d\n", (int)tret);
}

