#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

int main() {

  /* Create a set of signals */
  sigset_t waitset;
  /* Empty it */
  sigemptyset(&waitset);
  /* Add some signals */
  sigaddset(&waitset, SIGINT);
  sigaddset(&waitset, SIGUSR1);

  /* Block the signals in the waitset list
   * NOTE: SIG_BLOCK means "add signals in waitset to the already blocked ones"
   * NOTE: the other signals will still have default behaviour, aka terminate
   * the program
   */
  sigprocmask(SIG_BLOCK, &waitset, NULL);

  /* Information on signal */
  siginfo_t info;

  struct timespec timeout;
  timeout.tv_sec = 10;
  timeout.tv_nsec = 0;

  /* Wait for specified timeout (and then return -1) or until one of the
   * signals in waitset is received. */
  int result = sigtimedwait(&waitset, &info, &timeout);

  if (result < 0) {
    int errnum = errno;
    char * error_mess = malloc(sizeof(char) * 100);
    strerror_r(errnum, error_mess, 99);
    printf("\nTimeout. %d\n", result);
    printf("Error: %s", error_mess);
    free(error_mess);
  } else {
    printf("\nSignal received. %d\n", result);
  }

  return 0;
}
