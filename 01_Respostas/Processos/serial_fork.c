#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  pid_t pid_filho;

  for(int i=0; i < argc; i++) {
    pid_filho = fork();
    if (pid_filho == 0) {
      execlp(argv[i], argv[i], (char*)NULL);
    } 
  } 

  return 0;
}