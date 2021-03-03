#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main () {
  int pid;
  int fd[2];
  pipe(fd);
  pid = fork();
  int count = 0;

  if (count == 0) {
    if(pid == 0) // Codigo do filho
    {
      char buffer_filho[100];
      char msg_filho[] = "FILHO: Pai, qual é a verdadeira essência da sabedoria?";

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
      char msg_pai[] = "PAI: Não façais nada violento, praticai somente aquilo que é justo e equilibrado.";

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
  
  count ++;

  if(count == 1) {
    if(pid == 0) // Codigo do filho
    {
      char buffer_filho[100];
      char msg_filho[] = "FILHO: Mas até uma criança de três anos sabe disso!";

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
      char msg_pai[] = "PAI: Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...";

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