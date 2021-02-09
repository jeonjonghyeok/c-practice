#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

void *func_t(void *data);


int main(int argc, char *argv[])
{
  int i, serv_sock, cli_sock;
  struct sockaddr_in cli_addr, serv_addr;

  if((serv_sock = socket(AF_INET,SOCK_STREAM, 0 ))< 0)
  {
    perror("socket create error");
    exit(0);
  }

  bzero(&serv_addr,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
  {
    perror("bind error: ");
    exit(0);
  }

  if(listen(serv_sock, 5)== -1)
  {
    perror("listen error: ");
    exit(0);
  }

  int thread_cnt = (int)argv[2];

  pthread_t threads[thread_cnt];


  for(i=0;i<thread_cnt;i++)
  {
    pthread_create(&threads[i], NULL, func_t, (void *)i);

  }
  return 0;
}

void *func_t(void *data)
{


}
