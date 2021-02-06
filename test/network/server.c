#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string.h>
#define BUFSIZE 1024


int main(int argc, char **argv) {
  int serv_sock;
  int clnt_sock;
  int str_len;

  char message[BUFSIZE];

  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;

  int clnt_addr_size;


  if(argc !=2){
    printf("Usage: %s <port>\n",argv[0]);
      exit(1);
  }

  serv_sock = socket(PF_INET,SOCK_STREAM,0);
  if(serv_sock == -1)
    exit(1);

  memset(&serv_addr,0,sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));
  
  if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
    exit(1);

  if(listen(serv_sock,5) == -1)
    exit(1);

  clnt_addr_size = sizeof(clnt_addr);

  
  clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr, &clnt_addr_size);
  if(clnt_sock == -1)
    exit(1);

  while((str_len = read(clnt_sock,message,BUFSIZE))!=0){
    write(clnt_sock,message,str_len);
    write(1,message,str_len);

  }
  close(clnt_sock);


  return 0;
}

