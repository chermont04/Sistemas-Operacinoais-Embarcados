#include<stdio.h>

void error_fopen(FILE *olaMundo) {
  if(olaMundo == NULL) {
    printf("Erro na abertura do arquivo\n");
    exit(-1);
  }
}

int main () {
  FILE *ola_mundo;

  char str[] = "Ola Mundo!";

  ola_mundo = fopen("ola_mundo.txt", "w");

  error_fopen(ola_mundo);

  fwrite(str, 1, sizeof(str), ola_mundo);

  fclose(ola_mundo);

  return 0;
}