#include<stdio.h>
#include<string.h>

int main(int argc, char **argv) {
  FILE *file;

  char palavra[80];
  char texto[200];
  int i=0, count, aux, aux2, ocorrencias;

  strcpy(palavra, argv[1]);

  file = fopen(argv[2], "r");

  while (!feof(file)) {
    texto[i] = fgetc(file);
    i++;
  }
  texto[i-1]='\0';

  for (int j = 0; j < strlen(texto); j++) {
    if(palavra[0] == texto[j]) {
      aux = j;
      aux2 = 0;
      while(aux2<strlen(palavra) && aux < strlen(texto)) {
        if(palavra[aux2] != texto[aux]) {
          aux = strlen(texto);
        } else {
          if (aux2 == (strlen(palavra)-1))
            ocorrencias++;
          aux++;
          aux2++;
        }

      }
    }
  }
  fclose(file);

  printf("'%s' ocorre %d vezes em '%s'\n", palavra, ocorrencias, argv[2]);

  return 0;
}