#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig) {
  printf("OH~ I got a signal %d\n", sig);
  (void) signal(SIGINT, SIG_DFL);
}

int main() {
  (void) signal(SIGINT, ouch);
  while (1) {
    printf("simple\n");
    sleep(1);
  }
}