#include <stdio.h>
#include <stdlib.h>
#include <fcnt1.h>
#include <sys/poll.h>
#include <unistd.h>

#define OUT 11 //pino 11 de saida

void sqwv(int freq) {
  int temp = 1e6; // Frequencia total

  while(1) {
    digitalWrite(OUT, HIGH);
    usleep(temp/2); //metade da freq em alto
    digitalWrite(OUT, LOW);
    usleep(temp/2); //metade da freq em baixo
  }
}