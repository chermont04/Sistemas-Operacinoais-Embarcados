#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int fileSize (char *file) {
  char texto[200];
  int fd,size;
  fd = open(file, O_RDWR);
  size = lseek(fd, 0, SEEK_END);
  close(fd);

  return size;
}

int main(int argc, char **argv) {

char palavra[80];
char texto[200];
int fd,i=0, count, aux, aux2, ocorrencias;
int size;

size = fileSize(argv[2]);
strcpy(palavra, argv[1]);

fd = open(argv[2], O_RDWR);

read(fd, texto, size);
texto[size] = '\0';

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
close(fd);

printf("'%s' ocorre %d vezes em '%s'\n", palavra, ocorrencias, argv[2]);

return 0;
}