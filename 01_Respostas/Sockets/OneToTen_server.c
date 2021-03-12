#include "server_funcs.h"

char socket_name[100];
int socket_id;

void end_server(int signum);

int main (int argc, char* const argv[]) {
  //Socket com estrutura padrão
  struct sockaddr socket_struct;

  signal(SIGINT, end_server) ;
  // Nome do socket = argv[1]
  strcpy(socket_name, argv[1]);
  // Criamos um socket de stream do tipo local e recebemos em socket_id
  socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);
  socket_struct.sa_family = AF_LOCAL;
  strcpy(socket_struct.sa_data, socket_name);

  bind(socket_id, &socket_struct, sizeof(socket_struct));

  listen(socket_id, 10); // colocamos o socket em modo passivo

  //Criar a conexão com o cliente
  while(1) {
    int message;
    //Estrutura padrão pro socket
    struct sockaddr client;
    int socket_id_client;
    socklen_t client_len;
    // Aceitar a conexão com o servidor
    socket_id_client = accept(socket_id, &client, &client_len);
    //Le a mensagem do cliente
    read(socket_id_client, &message, 1);
    fprintf(stderr, "Mensagem = %d\n", message);
    //finalizar o servidor
    if (message == 10) {
      end_server(0);
    }
    //Encerra a conecção com o cliente
    close(socket_id_client);

  }

  return 0;
}

void end_server(int signum) {
  fprintf(stderr, "Fechando servidor local\n");
  unlink(socket_name);
  close(socket_id);
  exit(0);
}

