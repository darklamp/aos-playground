#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  const char *myfifo = "/tmp/myfifo";
  if (mkfifo(myfifo, 0666) != 0) {
    printf("Cannot create fifo.\n");
    return 1;
  }

  /* Since O_NONBLOCK is not set, opening for write only will make the write
   * hang until someone opens for reading! */
  int fd = open(myfifo, O_WRONLY);
  if (fd <= 0) {
    printf("Cannot open fifo\n");
    unlink(myfifo);
    return 1;
  }
  float data = 10;
  int nb = write(fd, &data, sizeof(data));
  if (nb == 0) {
    printf("Write error\n");
  }

  printf("OK\n");

  close(fd);
  unlink(myfifo);
  return 0;
}
