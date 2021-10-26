#include <bits/types/sigset_t.h>
#include <fcntl.h>
#include <math.h>
#include <mqueue.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MSG_PRIO_HIGH 2
#define MSG_PRIO_MED 1
#define MSG_PRIO_LOW 0
mqd_t mq;

void handler() {
  printf("Closing..");
  mq_close(mq);
  mq_unlink("/myQueue");
  exit(0);
}

int main() {
  struct mq_attr mq_attrs;
  mq_attrs.mq_maxmsg = 10;
  mq_attrs.mq_msgsize = 100;
  mq_attrs.mq_flags = 0;
  mq_attrs.mq_curmsgs = 0;
  time_t now;
  time(&now);
  mq = mq_open("/myQueue", O_RDONLY | O_CREAT, 0664, &mq_attrs);
  printf("IS NULL: %s\n", mq == -1 ? " YES" : "NO");

  struct sigaction sa;
  sa.sa_handler = &handler;

  sigaction(SIGINT, &sa, NULL);

  char buffer[101];
  unsigned int msg_prio;
  while (true) {
    int received_bytes = mq_receive(mq, buffer, 100, &msg_prio);
    if (received_bytes > 0) {
      printf("%s %s %100s \n", ctime(&now),
             (msg_prio == MSG_PRIO_LOW ? "[LOW]" : (msg_prio == MSG_PRIO_MED ? "[MEDIUM]" : "[HIGH]")),
             buffer);
    } else {
      perror("Errore");
    }
  }
}