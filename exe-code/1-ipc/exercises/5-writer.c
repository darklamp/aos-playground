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
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct person {
  char name[100];
  char surname[100];
  uint16_t year_of_birth;
};
struct person * people;
void handler() {
  printf("Closing..");
  munmap(people, 3 * sizeof(struct person));
  shm_unlink("/mySHM");
  exit(0);
}

int main() {
  int shm = shm_open("/mySHM", O_RDWR | O_CREAT, 0664);
  ftruncate(shm, sizeof(struct person));
  people =
      mmap(NULL, sizeof(struct person), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
  struct sigaction sa;
  sa.sa_handler = &handler;
  sigaction(SIGINT, &sa, NULL);
  strcpy(people[0].name, "Federico");
  strcpy(people[0].surname, "Reghenzani");
  people[0].year_of_birth = 1992;
  
  exit(0);

}