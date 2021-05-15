#include <wiringPi.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

//Definicao das portas e frequencias
#define SAIDA 7
#define ENTRADA 2
#define freq_100 (1e6/100) 
#define freq_75 (1e6/75)  
#define freq_50 (1e6/50) 
#define freq_25 (1e6/25)
#define freq_0  0

half_period == freq_0;

// alternancia de frequencia, pela ordem estabelecida
void change_freq()
{
	if (half_period == freq_0) {
    half_period = freq_25;
  }
  if (half_period == freq_25) {
    half_period = freq_50;
  }
  if (half_period == freq_50) {
    half_period = freq_75;
  }
  if (half_period == freq_75) {
    half_period = freq_100;
  }
  if (half_period == freq_100) {
    half_period = freq_0;
  }


}

int main(void)
{
	pid_t filho;
	wiringPiSetup();
	pinMode(SAIDA, OUTPUT);
	pinMode(ENTRADA, INPUT);
	pullUpDnControl(ENTRADA, PUD_UP);
	signal(SIGUSR1, change_freq);
	filho = fork();
	if(filho==0)
	{
		while(1)
		{
			digitalWrite(SAIDA, HIGH);
			usleep(half_period);
			digitalWrite(SAIDA, LOW);
			usleep(half_period);
		}
	}
	else
	{
		while(1)
		{
			while(digitalRead(ENTRADA)>0);
			kill(filho,SIGUSR1);
			while(digitalRead(ENTRADA)==0);
			usleep(300000); //arbitrado
		}
	}
}