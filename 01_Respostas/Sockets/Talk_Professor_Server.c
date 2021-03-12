#include "server_funcs.h"

int main (int argc, char* const argv[]) {
  int socket_id;
  struct sockaddr socket_struct;
  char msg_in[100];
  char msg_out[100];

  if(argc < 2) {
    puts("Modo de uso: ");
    printf("%s NOME_SOCKET\n", argv[0]);
    exit(1);
  }

  socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);
  socket_struct.sa_family = AF_LOCAL;
  strcpy(socket_struct.sa_data, argv[1]);
  bind(socket_id, &socket_struct, sizeof(socket_struct));
  listen(socket_id, 10);

  struct sockaddr cliente;
  int socket_id_cliente, end_server_ok;
  socklen_t cliente_len;

  socket_id_cliente = accept(socket_id, &cliente, &cliente_len);

  read(socket_id_cliente, msg_in, 100);
  printf("SERVIDOR: %s\n", msg_in);
  strcpy(msg_out, "Não façais nada violento, praticai somente aquilo que é justo e equilibrado");
  write(socket_id_cliente, msg_out, 100);
  sleep(1);
  read(socket_id_cliente, msg_in, 100);
  printf("SERVIDOR: %s\n", msg_in);
  strcpy(msg_out,"Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
  write(socket_id_cliente, msg_out, 100);
  sleep(1);
  close(socket_id_cliente);
  close(socket_id);

  

  return 0;
}