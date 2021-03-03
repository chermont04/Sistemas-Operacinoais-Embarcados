#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
  pid_t pid_filho[3];
  
  for (int i = 0; i < strlen(pid_filho); i++) {
    pid_filho[i] = fork();

    if(pid_filho[i] == 0) {
      printf("Processo filho %d pid: %d\n", i+1, getpid());
      sleep(1);
      return 0;
    }
  }

  sleep(1);
  printf("Processo pai pid: %d\n", getpid());

  return 0;
}