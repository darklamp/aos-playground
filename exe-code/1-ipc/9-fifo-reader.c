#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  const char *myfifo = "/tmp/myfifo";
  /* Since O_NONBLOCK is not set, opening for read only will make the read hang
    until someone opens for reading! Note: in the case someone already has
    opened for writing, the read will not hang. */
  int fd = open(myfifo, O_RDONLY);
  if (fd <= 0) {
    printf("Cannot open fifo\n");
    return 1;
  }

  float data;
  int nb = read(fd, &data, sizeof(data));
  if (nb == 0) {
    printf("Read error\n");
    return 1;
  }

  printf("Read: %f\n", data);

  close(fd);
  return 0;
}
