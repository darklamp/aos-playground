#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
uint8_t counter = 0;
void handler() {
  printf("\nSOMMA: %d\n", counter);
  exit(0);
}
int main(int argc, char **argv) {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));

  sa.sa_handler = &handler;

  sigaction(SIGUSR1, &sa, NULL);

  sigset_t signalset;
  sigemptyset(&signalset);
  sigaddset(&signalset, SIGTERM);
  sigprocmask(SIG_BLOCK, &signalset, NULL);

  for (uint8_t i = 0; i < 100; i++) {
    printf("%d ", i);
    fflush(stdout);
    sleep(1);
  }
  printf("\nSOMMA: %d\n", counter);
  return 0;
}