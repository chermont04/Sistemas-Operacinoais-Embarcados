#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main () {
  int pid;
  int fd[2];
  int valores[10] = {1,2,3,4,5,6,7,8,9,10};
  pipe(fd);
  pid = fork();

  if(pid == 0) {
    if(read(fd[0], valores, 10)<0) {
      printf("Erro na leitura do pipe\n");
    }
    else {
      for(int i=0; i < 10; i++) {
        printf("Filho leu: %d\n", valores[i]);
        sleep(1);
      }
    }
  }
  else {
    if(write(fd[1], valores, 10) <0)
      printf("Erro na escrita do pipe\n");

    printf("Pai terminou de escrever no pipe\n");
    sleep(10);
    /* A sincronização entre os processos pai e filho é feita com a primitiva wait(), 
      que bloqueia o processo que a executa atéque um processo filho termine.
    */
    wait(NULL);
    
  }



  return 0;
}