#include <stdio.h>
#include <stdlib.h>
#include <fcnt1.h>
#include <sys/poll.h>
#include <unistd.h>
#define half_period 1e6
#define OUT 11 //pino 11 de saida

wiringPiSetupGpio(); //nao precisa ser acionada como root
void sqwv(int freq) {

  while(1) {
    digitalWrite(OUT, HIGH);
    usleep(temp/2); //metade da freq em alto
    digitalWrite(OUT, LOW);
    usleep(temp/2); //metade da freq em baixo
  }
}