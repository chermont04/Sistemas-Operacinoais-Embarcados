#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main (int argc, const char *argv[]) {
int fd = open("ola_mundo.txt", O_WRONLY | O_CREAT, S_IRWXU);

char str[] = {"Ola mundo!\0"};

write(fd, str , strlen(str));


write(fd,"\n",1);
close(fd);

return 0;
}