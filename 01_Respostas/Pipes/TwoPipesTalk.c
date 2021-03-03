#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main () {
  int pid_filho1;
  int fd[2];
  pipe(fd);
  pid_filho1 = fork();

    if(pid_filho1 == 0) // Codigo do filho
    {
      char buffer_filho[100];
      char msg_filho[] = "FILHO1: Quando o vento passa, é a bandeira que se move.";

      if(write(fd[1], msg_filho, sizeof(msg_filho)) < 0)
        printf("Erro na escrita do pipe\n");

      if(read(fd[0], buffer_filho, sizeof(msg_filho))<0)
        printf("Erro na leitura do pipe\n");
      else 
        printf("%s\n", buffer_filho);

    }
    else { // processo para o segundo filho
    int pid_filho2;
    pipe(fd);
    pid_filho2 = fork();
      if(pid_filho2 == 0) {
      char buffer_filho[100];
      char msg_filho[] = "FILHO2: Não, é o vento que se move.";

      if(write(fd[1], msg_filho, sizeof(msg_filho)) < 0)
        printf("Erro na escrita do pipe\n");

      if(read(fd[0], buffer_filho, sizeof(msg_filho))<0)
        printf("Erro na leitura do pipe\n");
      else 
        printf("%s\n", buffer_filho);

      }
      else //codigo do pai
    {
      char buffer_pai[200];
      char msg_pai[] = "PAI: Os dois se enganam. É a mente dos senhores que se move.";

      sleep(1);

      if(write(fd[1], msg_pai, sizeof(msg_pai))<0)
        printf("Erro na leitura do pipe\n");
        
      wait(NULL);
      
      if(read(fd[0], buffer_pai, sizeof(msg_pai))<0)
        printf("Erro na leitura do pipe\n");
      else 
        printf("%s\n", buffer_pai);
    }

    }
  
 

  return 0;
}