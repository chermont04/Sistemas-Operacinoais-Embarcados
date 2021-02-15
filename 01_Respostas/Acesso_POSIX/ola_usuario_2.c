#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char **argv) {
char name[80];
int fd;

strcpy(name,argv[1]);

fd = open(strcat(name,".txt"), O_RDWR | O_CREAT, S_IRWXU);

write(fd, "Nome: ", strlen("Nome: "));
write(fd, argv[1], strlen(argv[1]));
write(fd, "\nIdade: ", strlen("\nIdade: "));
write(fd, argv[2], strlen(argv[2]));
write(fd, " anos", strlen(" anos"));

close(fd);

return 0;
}