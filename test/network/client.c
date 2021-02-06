#include <stdio.h>
#include <arpa/inet.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 1024

int main(int argc, char **argv){
  int sock;
  struct sockaddr_in serv_addr;
  char message[BUFSIZE];
  int str_len;
  

  if(argc != 3){
    printf("Usage : %s <IP> <Port> \n", argv[0]);
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock== -1 )
    exit(1);

  memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))== -1)
    exit(1);

  while(1){
    fputs("전송할 메세지를 입력하세요(q to quit): ",stdout);
    fgets(message, BUFSIZE, stdin);

    if(!strcmp(message,"q\n"))
      break;
    write(sock,message, strlen(message));


    str_len = read(sock,message, BUFSIZE-1);
    message[str_len]= 0;
    printf("서버로 부터 전송된 메세지: %s\n",message);
  }

  close(sock);
  return 0;
}
