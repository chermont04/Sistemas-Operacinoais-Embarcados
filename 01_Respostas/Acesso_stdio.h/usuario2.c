#include<stdio.h>
#include<string.h>

int main(int argc, char **argv) {
  FILE *file;

  char copyarg[80];
  char idade[80];

  strcpy(copyarg, argv[1]);
  strcpy(idade, argv[2]);

  file = fopen(strcat(argv[1],".txt"), "wb");

  fprintf(file, "Nome: %s\n", copyarg);
  fprintf(file,"Idade: %s anos\n", idade);

  fclose(file);

  return 0;
}