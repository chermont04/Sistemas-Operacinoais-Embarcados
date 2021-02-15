#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
char name[80],copyname[81],age[3];
int fd;

printf("Digite o seu nome: ");
gets(name);

strcpy(copyname, name);

printf("Digite a sua idade: ");
gets(age);

fd = open(strcat(name,".txt"), O_RDWR | O_CREAT, S_IRWXU);

write(fd, "Nome: ", strlen("Nome: "));
write(fd, copyname, strlen(copyname));
write(fd, "\nIdade: ", strlen("\nIdade: "));
write(fd, age, strlen(age));
write(fd, " anos", strlen(" anos"));

close(fd);

return 0;
}