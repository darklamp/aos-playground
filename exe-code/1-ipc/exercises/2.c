#include <bits/types/sigset_t.h>
#include <math.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
float calc4(uint8_t start) {
  float out = 0;
  start++;
  for (uint8_t i = start; i < start + 4; i++) {
    printf("%d ", i);
    out += pow(1.5, i);
  }
  return out;
}
void main_func(int start, int fd[]) {
  FILE *out = fdopen(fd[1], "w");
  fprintf(out, "%f ", calc4(start));
  fclose(out);
  close(fd[1]);
}
int main() {
  int pid1, pid2 = -1;
  int fd[2];
  pipe(fd);
  pid1 = fork();

  if (pid1 != 0) {
    pid2 = fork();
    if (pid2 == 0) {
      close(fd[0]);
      main_func(4, fd);
      exit(0);
    } else {
      main_func(8, fd);
      wait(NULL);
      wait(NULL);
      FILE *out = fdopen(fd[0], "r");
      float res[3];
      fscanf(out, "%f %f %f ", &res[0], &res[1], &res[2]);
      printf("SUM: %f\n", res[0] + res[1] + res[2]);
      close(fd[0]);
      exit(0);
    }
  } else { // second thread
    close(fd[0]);
    main_func(0, fd);
    exit(0);
  }
  exit(0);
}