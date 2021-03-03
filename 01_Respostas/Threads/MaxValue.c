/*
O Exercicio não está completo e funcional
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4

static pthread_mutex_t mutexLock;
int count = 0;
long int max_thread;

void *max_value_thread(void *t,long int a[50000], long int tamanho) {
  long int i;
  int max;
  long my_id = (long)t;

  for (i=count; i < 12500; i++) {
    pthread_mutex_lock(&mutexLock);
    count ++;
    if(i = 0) {
      max_thread = a[i];
    }
    else {
      if(max_thread < a[i]) {
        max_thread = a[i];
      }
    }
  }
  printf("O maior valor da thread %ld, foi: %d\n", my_id, max);
}

int max_Value(long int a[], long int tamanho);

int main() {
long int v[50000];
for(long int i=0; i < 50000; i++) {
  v[i] = random();
}
int i, rc;
long t1 = 1, t2 = 2, t3 = 3, t4 = 4;
int max_func;
pthread_t threads[4];

pthread_mutex_init(&mutexLock, NULL);

pthread_create(&threads[0], NULL, max_value_thread(NULL, v, 50000), (void *)t1);
pthread_create(&threads[1], NULL, max_value_thread(NULL, v, 50000), (void *)t2);
pthread_create(&threads[2], NULL, max_value_thread(NULL, v, 50000), (void *)t3);
pthread_create(&threads[3], NULL, max_value_thread(NULL, v, 50000), (void *)t4);

for (i = 0; i < NUM_THREADS; i++) {
  pthread_join(threads[i], NULL);
}

max_func = max_Value(v, 50000);

pthread_mutex_destroy(&mutexLock);
printf("Valor pelo metodo (a): %d\n", max_func);
pthread_exit (NULL);
  return 0;
}


int max_Value(long int a[], long int tamanho){
  int max;
  for (int i = 0; i < tamanho; i++) {
    if(i = 0) {
      max = a[i];
    }
    else {
      if(max < a[i]) {
        max = a[i];
      }
    }
  }
  return max;
}

