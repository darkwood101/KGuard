#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void read_write_bee(int fd, int write_fd, char* buf) {
    ssize_t r = read(fd, buf, 10000);
    assert(r > 0);
    r = write(write_fd, buf, 10000);

    off_t off = lseek(fd, 0, SEEK_SET);
    assert(off == 0);
}

int main() {
  char buf[10000];
  int fd = open("docs/bee.txt", O_RDONLY);
     int	write_fd = open("docs/write.txt", O_CREAT | O_RDWR);
  for (int i = 0; i < 10000; ++i) {
    read_write_bee(fd, write_fd, buf);
  }
  return 0;
}
