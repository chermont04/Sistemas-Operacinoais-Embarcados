#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int v_global = 0; // Variavel global para este exemplo

void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}

int main () {
  pid_t pid_filho;

  for(int i=0; i < 3; i++) {
    pid_filho = fork();
    if(pid_filho == 0) {
      Incrementa_Variavel_Global(getpid());
      i = 3;
    }
  }

  return 0;
}

//Como podemos perceber pela execução do código acima, a variavel global v_global é incrementada apenas 1x.
