#include <bits/types/sigset_t.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
char str[20];
int fd = -1;

void ex() {
  close(fd);
  unlink(str);
  exit(0);
}
int main() {
  const char *myfifo = "/tmp/myfifo.";
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = &ex;
  sigaction(SIGINT, &sa, NULL);
  do {
    uint8_t count = 0;
    sprintf(str, "%s%u", myfifo, count);
    fd = open(str, O_RDONLY);
    count++;
  } while (fd == -1);
  mkfifo(str, 0600);
  printf("PIPE NAME: %s\n", str);
  fflush(stdout);
  char out[20];
  int byt = read(fd, &out, 20);
  if (byt == -1) {
    printf("\nThe fuck is that string length\n");
    exit(-1);
  } else {
    printf("%s", out); // nciò voglia di reversarla
    fflush(stdout);
  }
  exit(0);
}