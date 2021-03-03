#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT_MAX 10

void *countSum(void *tid) {
  long id = (long)tid;
  int count=0;
  while(count < COUNT_MAX) {
    count ++;
    printf("Contador em %d\n", count);
    sleep(1);
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t t1;
  int create;
  long num;
  num = 1;
  // Criando a thread
  create = pthread_create(&t1, NULL, countSum, (void *)num);

  pthread_join(t1, NULL);
  sleep(1);

  return 0;
}

