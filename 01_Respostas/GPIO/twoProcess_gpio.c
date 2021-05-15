#include <stdio.h>
#include <stdlib.h>
#include <fcnt1.h>
#include <sys/poll.h>
#include <unistd.h>

#define OUT 11
#define IN 7
#define half_period_max (1e6/2) //meio periodo max == freq 1hz
#define half_period_min (1e6/128) //meio periodo min == freq 64hz

void change_freq() {
  half_period /= 2; //divide o perido por 2 (dobrar o periodo anterior)
  if(half_period < half_period_min)
    half_period = half_period_max; // retorna a freq para 1hz, quando maior que 64hz
}

int main() {
  WiringPiSetupGpio();
  pinMode(OUT, OUTPUT);
  pinMode(IN, INPUT);
  pullUpDnControl(IN, PUD_UP);
  signal(SIGUSR1, change_freq); //chama a funcao para mudar a frequencia pelo sinal
  pid_t filho;
  filho = fork();

  if(filho == 0)
  {
    while(1) {
      digitalWrite(OUT, HIGH);
      usleep(half_period);
      digitalWrite(OUT, LOW);
      usleep(half_period);
    }
  }
  else {
    while(1) {
      while(digitalRead(IN) > 0);
      kill(filho, SIGUSR1);
      while(digitalRead(IN) == 0);
      usleep(300000); //arbitrado
    }
  }
}