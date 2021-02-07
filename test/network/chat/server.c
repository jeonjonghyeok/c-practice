#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>

int main(int argc, char *argv[]){
  int serv_sock, cli_sock;
  int cli_addr_size;
  struct sockaddr_in serv_addr, cli_addr;
  pthread_t t_id;
  

  if(argc != 2){
      exit(1);
  }

  serv_sock = socket(PF_INET,SOCK_STREAM,0);
  if(serv_sock == -1)
    exit(1);

  memset(&serv_addr,0,sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));


  if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
    exit(1);

  if(listen(serv_sock,5)==-1)
    exit(1);

  cli_addr_size = sizeof(cli_addr);

  while(1){
   cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, &cli_addr_size);

   pthread_create(&t_id, NULL, )



  }

   


  return 0;
}

void *handle_cli(void *arg){
  int cli_sock = *((int *)arg);


}
