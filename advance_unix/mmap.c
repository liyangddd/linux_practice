#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#define BUF_SIZE 4096
#define FILEPATH  "test.pcap"

void err_exit(char *err) {
	perror(err);
	exit(-1);
}

int main(int argc, char **argv) {
	int fd, i;
	char *ptr;
	size_t filesize, mmapsize, pagesize;

	if (argc != 3) {
		perror("usage: <filesize> <mmapsize>");
		exit(-1);
	}
	filesize = atoi(argv[1]);
	mmapsize = atoi(argv[2]);

	fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, 0660);//S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP
	if (fd == -1)
	{
		perror("open file error");
		exit(-1);
	}
	if (lseek(fd, filesize - 1, SEEK_SET) == -1)
		err_exit("lseek error");
	write(fd, "", 1);

	ptr = mmap(NULL, mmapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
		err_exit("mmap error");
	if (close(fd) == -1)
		err_exit("close file error");

	if ((pagesize = sysconf(_SC_PAGESIZE)) == -1)
		err_exit("sysconf error");
	printf("PAGESIZE = %ld\n", (long)pagesize);

	size_t maxsize = (filesize > mmapsize ? filesize : mmapsize);
	for (i = 0; i < maxsize; i += pagesize)
	{
		printf("ptr[%d] = %d\n", i, ptr[i]);
		ptr[i] = 1;
		printf("ptr[%d] = %d\n", i + pagesize - 1, ptr[i + pagesize - 1]);
		ptr[i + pagesize - 1] = 1;
	}
	printf("ptr[%d] = %d\n", i, ptr[i]);
	exit(0);
}		
