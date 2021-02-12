#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
  int sock;
  char *name;
  char tmp[10];
  struct sockaddr_in serv_addr;

  if(argc != 4)
  {
    printf("Usage : %s <ip> <port> <name> \n",argv[0]);
    exit(1);
  }
  name = argv[3];

  sock = socket(PF_INET,SOCK_STREAM, 0);
  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))== -1)
  {
    printf("connect error");
    exit(1);
  }

  
  printf("a b operation 입력\n예시: 3 2 +\n");
  scanf("%s",tmp);
  printf("%s",tmp);

  printf("name: %s\n",name);
  write(sock, name, sizeof(name));
  char buf[100];
  int str_len;

    str_len = read(sock,buf,99);
    buf[str_len] = 0;
    printf("buf = %s",buf);


  close(sock);
  return 0;
}
