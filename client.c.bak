#include "client.h"
#include <ctype.h>

int main(){
  int server_fifo_fd;
  int client_fifo_fd;
  int times_to_send;
  struct data_to_pass_st my_data;
  char client_fifo[256];
  
  server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
  if (server_fifo_fd == -1) {
    fprintf(stderr, "SORRY, no server\n");
    exit(EXIT_FAILURE);
  }
  
  my_data.client_pid = getpid();
  sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);//client_%d_fifo 
  if (mkfifo(client_fifo, 0777) == -1) {
    fprintf(stderr, "Sorry, can not make %s\n", client_fifo);
    exit(EXIT_FAILURE);
  }
  for (times_to_send = 0; times_to_send < 5; times_to_send++) {
    sprintf(my_data.some_data, "Hello from %d", my_data.client_pid);
    printf("%d sent %s", my_data.client_pid, my_data.some_data);
    write(server_fifo_fd, &my_data, sizeof(my_data));
    client_fifo_fd = open(client_fifo, O_RDONLY);
    if (client_fifo_fd != -1) {
      if (read(client_fifo_fd, &my_data, sizeof(my_data)) > 0) {
	printf(", received: %s\n", my_data.some_data);
      }
      close(client_fifo_fd);
    }
  }
  close(server_fifo_fd);
  unlink(client_fifo);
  exit(EXIT_SUCCESS);
}
