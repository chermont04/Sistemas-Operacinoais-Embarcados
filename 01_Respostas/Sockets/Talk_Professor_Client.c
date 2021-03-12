#include "server_funcs.h"

int main (int argc, char* const argv[]) {
  if(argc < 3) {
    puts("Modo de Uso:");
    printf("%s NOME_SOCKET\n", argv[0]);
    exit(1);
  }
  int socket_id;
  struct sockaddr name;
  int lenght;
  char msg_in[100];
  char msg_out[100];

  socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);
  name.sa_family = AF_LOCAL;
  strcpy(name.sa_data, argv[1]);
  connect(socket_id, &name, sizeof(name));

  strcpy(msg_out, "Pai, qual é a verdadeira essência da sabedoria?");
  write(socket_id, msg_out, 100);
  sleep(1);
  read(socket_id, msg_in, 100);
  printf("CLIENTE: %s\n", msg_in);
  strcpy(msg_out, "Mas até uma criança de três anos sabe disso!");
  write(socket_id, msg_out, 100);
  sleep(1);
  read(socket_id, msg_in, 100);
  printf("CLIENTE: %s\n", msg_in);
  
  close(socket_id);
  return 0;
}