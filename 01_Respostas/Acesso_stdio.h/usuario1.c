#include<stdio.h>
#include<string.h>

int main() {
  FILE *file;

  char name[80],copyname[81];
  int age;

  printf("Digite o seu nome: ");
  scanf("%s", name);

  strcpy(copyname, name);

  printf("Digite a sua idade: ");
  scanf("%d", &age);

  file = fopen(strcat(name,".txt"), "w");

  fprintf(file, "Nome: %s\n", copyname);
  fprintf(file,"Idade: %d anos\n", age);

  fclose(file);

  return 0;
}