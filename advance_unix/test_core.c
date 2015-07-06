#include <pwd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
static void my_alarm(int signo) {
  struct passwd *rootptr;
  printf("in signal handler\n");
  if ((rootptr = getpwnam("root")) == NULL) {
    perror("getpwnam(root) error");
    exit(-1);
  }
  alarm(1);
}

int main(void) {
  struct passwd *ptr;
  signal(SIGALRM, my_alarm);
  alarm(1);
  for (;;) {
    if ((ptr = getpwnam("sar")) == NULL) {
      perror("getpwnam(sar) error");
      exit(-1);
    }

    if (strcmp(ptr->pw_name, "sar") != 0)
      printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
  }
}
