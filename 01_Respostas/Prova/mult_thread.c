#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 50000
#define T_NUM 4
#define X 2.0


struct mult_thread_parms
{
  double *v_int;
  long int v_mult[N/T_NUM];
  int tam;
};

void* mult_thread(void* parameters)
{
  struct mult_thread_parms* p = (struct mult_thread_parms*) parameters;
  int tam;
  tam = p->tam;

  for(int i=0; i < tam; ++i) {
    p->v_mult[i] = ((long int)(p->v_int[i]))*X;
  }
  return NULL;
}

int main(void)
{
  double v_int[N];
  double v_final_mult[N];
  pthread_t threads[T_NUM];
  int i;
  struct mult_thread_parms mtps[T_NUM];

  printf("10 PRIMEIROS VALORES: ");
  for(i=0;i<N; i++)
  {
    v_int[i] = i;
    if(i < 10) {
      printf("%.1f ", v_int[i]);
    }
  }
  printf("\n");

  for(int j = 0; j < T_NUM; j++) {
    mtps[j].v_int = &(v_int[j*(N/4)]);
    mtps[j].tam = (N/T_NUM);

    pthread_create(&(threads[j]), NULL, &mult_thread, &(mtps[j]));
  }

  printf("10 Primeiro valores Multiplicados: ");

  printf("Resultado = ");
    for(i=0; i<T_NUM; i++) {
      pthread_join(threads[i], NULL);
      for(int j=0; j < N/T_NUM; j++) {
        v_final_mult[j+(i*N/T_NUM)] = (double)mtps[i].v_mult[j];
        if(i == 3 && j > 12490) {
          printf("%.1f ", v_final_mult[j+(i*N/T_NUM)]);
        }
      }
    }
    printf("\n");
  

    
  return 0;
}


