.PHONY: clean all
CC = gcc
CFLAGS = -g
BIN = tcpsrv01 tcpcli01 tcpsrvselect tcpcliselect  tcpclipoll tcpsrvepoll \
      udpsrv01 udpcli01 udpservselect01 daytimetcpcli1
INCLUDE = .
#下面这条语句在当前目录下找不到.c文件，就会去"./mylib"目录下寻找
vpath %.c ./mylib
all: $(BIN)
tcpsrv01:tcpsrv01.o signal.o
	${CC} ${CFLAGS} -o $@ tcpsrv01.o signal.o
tcpcli01: tcpcli01.o
	${CC} ${CFLAGS} -o $@ tcpcli01.o

tcpsrvselect: tcpsrvselect.o wrapsock.o
	${CC} ${CFLAGS} -o $@ tcpsrvselect.o wrapsock.o
tcpcliselect: tcpcliselect.o wrapsock.o
	${CC} ${CFLAGS} -o $@ tcpcliselect.o wrapsock.o

tcpclipoll:tcpclipoll.o wrapsock.o
	${CC} ${CFLAGS} -o $@ tcpclipoll.o wrapsock.o
#tcpsrvpoll:tcpsrvpoll.o wrapsock.o
#	${CC}  ${CFLAGS} -o $@ tcpsrvpoll.o wrapsock.o

tcpsrvepoll:tcpsrvepoll.o wrapsock.o
	${CC}  ${CFLAGS} -o $@ tcpsrvepoll.o wrapsock.o

udpsrv01: udpsrv01.o wrapsock.o
	${CC} ${CFLAGS} -o $@ udpsrv01.o wrapsock.o

udpcli01: udpcli01.o wrapsock.o
	${CC} ${CFLAGS} -o $@ udpcli01.o wrapsock.o

udpservselect01: udpservselect01.o wrapsock.o signal.o
	${CC} ${CFLAGS} -o $@ udpservselect01.o wrapsock.o signal.o

daytimetcpcli1: daytimetcpcli1.o wrapsock.o
	${CC} ${CFLAGS} -o $@ daytimetcpcli1.o wrapsock.o
#sigchldwait.o:sigchldwait.c
#	${CC} ${CPPFLAGS} -c sigchldwait.c
#tpcsrv01.o:tcpsrv01.c
#	${CC} ${CPPLAGS} -c tcpsrv01.c
#tcpcli01.o:tcpcli01.c
#	${CC} ${CPPLAGS} -c tcpcli01.c
%.o:%.c
	${CC} ${CFLAGS} -c $< -o $@ 
clean:
	rm -rf *.o ${BIN} *.c~ *.h~

INSTALLDIR = ./test_install
install: tcpsrv01
	@if [ -d $(INSTALLDIR) ];\
	  then\
	  cp tcpsrv01 $(INSTALLDIR);\
	  chmod a+x $(INSTALLDIR)/tcpsrv01;\
	  chmod og-w $(INSTALLDIR)/tcpsrv01;\
	  echo "Install in $(INSTALLDIR)";\
	else\
	  echo "Sorry, $(INSTALLDIR) does not exit";\
	fi
