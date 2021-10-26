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

void handler(mqd_t mq) {
  printf("Closing..");
  mq_close(mq);
  exit(0);
}

static char *rand_string(char *str, size_t size) {
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
  if (size) {
    --size;
    for (size_t n = 0; n < size; n++) {
      int key = rand() % (int)(sizeof charset - 1);
      str[n] = charset[key];
    }
    str[size] = '\0';
  }
  return str;
}

int main() {
  srand(time(NULL));
  struct mq_attr mq_attrs;
  mq_attrs.mq_maxmsg = 10;
  mq_attrs.mq_msgsize = 100;
  mq_attrs.mq_flags = 0;
  mq_attrs.mq_curmsgs = 0;
  mqd_t mq = mq_open("/myQueue", O_WRONLY | O_CREAT, 0664, &mq_attrs);
  struct sigaction sa;
  sa.sa_handler = &handler;
  sigaction(SIGINT, &sa, NULL);
  char * random_string = malloc(100);
  while (true) {
    usleep(500000);
    random_string = rand_string(random_string, 100);
    printf("%s\n", random_string);
    int send = mq_send(mq, random_string, strlen(random_string), rand() % 3);
  }
}