#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void my_handler(int sig_num) { printf("Received %d\n", sig_num); }

/*
➜  1-ipc git:(master)   ./outputs/5-signal-receiver
 // in another terminal
 ➜  1-ipc git:(master) pidof 5-signal-receiver
 21989
➜  1-ipc git:(master)   kill -10 21989 // sends signal 10 aka "SIGURS1" to process w/ PID 21989 
Received 10

*/

int main() {

  struct sigaction sa;
  int pid = getpid();

  memset(&sa, 0, sizeof(sa));

  sa.sa_handler = &my_handler;
  sigaction(SIGUSR1, &sa, NULL);

  while (1) {
    sleep(1);
  }
  return 0;
}
