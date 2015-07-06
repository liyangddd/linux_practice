#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  uid_t uid = getuid();
  printf("%d\n", uid);
  printf("%s\n", getlogin());
//   struct tm *time_ptr;
//   time_t the_time;
//   char buf[256];
//   
//   (void) time(&the_time);
//   //the_time = time(0);
//   time_ptr = localtime(&the_time);
//   printf("Raw time is %ld\n", the_time);
//   printf("date: %02d/%02d/%02d\n",
//   time_ptr->tm_year, time_ptr->tm_mon + 1, time_ptr->tm_mday);
//   printf("time: %02d:%02d:%02d\n",
//   time_ptr->tm_hour, time_ptr->tm_min, time_ptr->tm_sec);
//   printf("ctime:%s\n",  ctime(&the_time));
//   strftime(buf, 256, "%A %d %B, %H:%M:%S %p.", time_ptr);
//   printf("strftime: %s\n", buf);
//  
  exit(0); 
}