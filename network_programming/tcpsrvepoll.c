//该版本使用epoll代替poll
#include "myheader.h"
#define OPEN_MAX 1024
#define MAXEVENTS 64 
static int make_socket_non_blocking(int sfd) {
  int flags;
  if ((flags = fcntl(sfd, F_GETFL, 0)) == -1)
    err_quit("fcntl error 1");
  flags |= O_NONBLOCK;
  if (fcntl(sfd, F_SETFL, flags) == -1)
    err_quit("fcntl error 2");
  return 0;
}

int main(int argc, char **argv)
{
  int i, maxi, listenfd, connfd, sockfd;
  int nready;
  ssize_t n;
  char buf[MAXLINE];
  socklen_t clilen;
  struct epoll_event event, events[MAXEVENTS];
 
  struct sockaddr_in cliaddr, servaddr;
  listenfd = Socket(AF_INET, SOCK_STREAM, 0);
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  // 设置套接字选项避免地址使用错误:
  //结束服务器程序后“bind error: Address already in use” 
  int opt = 1;
  if ( setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    err_exit("setsockopt error\n");

  Bind(listenfd, (const struct sockaddr*)&servaddr, sizeof(servaddr));
  
  if (make_socket_non_blocking(listenfd) == -1) {
    err_exit("make_socket_non_blocking error");
  }
  Listen(listenfd, LISTENQ);
  
  int efd = epoll_create1(EPOLL_CLOEXEC);
  if (efd == -1)
    err_exit("epoll_create1 error");
  event.data.fd = listenfd;
  event.events = EPOLLIN | EPOLLET;  //读入,边缘触发方式  
  int s = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &event);
  if (s == -1)
    err_quit("epoll_ctl error");
  
  for( ; ; ) {
    int i;
    int nfds = epoll_wait(efd, events, MAXEVENTS, -1);
    for (i = 0; i < nfds; i++) {
      /* An error has occured on this fd, or the socket is not 
                 ready for reading (why were we notified then?) */   
      if ( (events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || 
	 (!(events[i].events & EPOLLIN))) {
	fprintf(stderr, "epoll error\n");
        close(events[i].data.fd);
        continue;
      }
      /* We have a notification on the listening socket, which 
                 means one or more incoming connections. */   
      else if (listenfd == events[i].data.fd) {
        for ( ; ; ) {
	  struct sockaddr cliaddr;
	  char hbuf[MAXLINE], sbuf[MAXLINE];
	  socklen_t clilen = sizeof(cliaddr);
	  int connfd = accept(listenfd, (const struct sockaddr*)&cliaddr,
&clilen);
          if (connfd == -1) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
              break;
            else { perror("accept DDDDDDD"); break;};
         
          }
	  //将地址转化为主机名或者服务名 
	  //flag参数:以数字名返回主机地址和服务地址   
	  int s = getnameinfo(&cliaddr, clilen, hbuf, sizeof(hbuf),
			      sbuf, sizeof(sbuf), NI_NUMERICHOST
                               | NI_NUMERICSERV);
           if (s == 0)  
             printf("Accepted connection on descriptor %d "  
                             "(host=%s, port=%s)\n", connfd, hbuf, sbuf);  
	   /* Make the connection socket non-blocking and add it to the 
                     list of fds to monitor. */   		 
           if (make_socket_non_blocking(connfd) == -1)
	     err_exit("make_socket_non_blocking connfd error");
	   event.data.fd = connfd;
	   event.events = EPOLLIN | EPOLLET;
	   if (epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &event) == -1)
	     err_exit("epoll_ctl error connfd");
	}
	continue;
      }
      else {
	/* We have data on the fd waiting to be read. Read and 
                 display it. We must read whatever data is available 
                 completely, as we are running in edge-triggered mode 
                 and won't get a notification again for the same 
                 data. */   
	int done = 0;
	for ( ; ;) {
	  ssize_t count = read(events[i].data.fd, buf, sizeof(buf));
	  if (count == -1) {
	    /* If errno == EAGAIN, that means we have read all 
                         data. So go back to the main loop. */ 
	    if (errno != EAGAIN) {
	      printf("read...");
	      done = 1;
	    }
	    break;
	  }
	  else if (count == 0) {
	    /* End of file. The remote has closed the 
                         connection. */ 
	    done = 1;  
            break;   
	  }
	  
	  Write(STDOUT_FILENO, buf, count);  //write to stdout
	}
	if (done) {
          printf("closed connection on descriptor %d\n", events[i].data.fd);
	  close(events[i].data.fd);
        }
      }
    }
  }
  close(listenfd);
  return EXIT_SUCCESS;
}
