#include "server_funcs.h"

int main (int argc, char* argv[]) {
  int socket_id;
  //Buscar o nome do socket do server
  char *socket_name;
  struct sockaddr name; //Estrutura basica do socket;

  socket_name = argv[1];
  // Escrever de 1 a 10 n servidor
  for (int i = 1; i <= 10; i++) {
    //Criar o socket local
    socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);
    name.sa_family = AF_LOCAL;
    strcpy(name.sa_data, socket_name);
    //Criar a conexão
    connect(socket_id, &name, sizeof(name));
    write(socket_id, &i, sizeof(i)+1);
    sleep(1);
    //Fecha o servidor
    close(socket_id);
  }

  return 0;
}
