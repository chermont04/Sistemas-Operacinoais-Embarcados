#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE* fp;
  char file_content;
  char *palavra, *arq;
  int N,cont_palavra;
  if(argc < 3)
  {
    printf("Indique a palvra para buscar e o arquivo aonde buscar!\n");
    return -1;
  }
  fp = fopen(argv[2], "r"); //Abri arquivo
  fseek(fp, 0, SEEK_END); // Vai para o final
  N = (int)ftell(fp); // Le o tamanho do arquivo
  fseek(fp, 0, SEEK_SET); //pula para o começo do arquivo

  file_content = (char *)malloc(N*sizeof(char)); //Aloca memoria dinamicamente
  fread(file_content, sizeof(char), N, fp); //Le todo o arquivo
  fclose(fp);

  palavra = argv[1];
  arq = file_content;
  cont_palavra = 0;
  arq = strstr(arq, palavra);
  while(arq != NULL) 
  {
    cont_palavra++;
    arq++;
  }

  printf("'%s' ocorre %d vezes no arquivo '%s'\n", palavra, cont_palavra, argv[2]);

  free(file_content);
  return 0;
}