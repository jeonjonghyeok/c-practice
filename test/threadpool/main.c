#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "queue.h"
#include <arpa/inet.h>
#include <string.h>
#define POOL_SIZE 10


void createPool();
void *func_main(void *data);
void *func_socket(void *data);
void createSocketThread(char *port);

pthread_mutex_t mutex;
pthread_cond_t cond_work;
pthread_cond_t cond_main;

struct task_queue *queue;

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    printf("./main port");
    exit(1);

  }


  createSocketThread(argv[1]);

  createQueue(queue);

  struct task task;
  task.sock_num = 10;
  task.task_num = 10;

  //enQueue(queue,task);
  //printf("%d\n",deQueue(queue).sock_num);


  createPool();




  return 0;
}

void createSocketThread(char *port)
{
  pthread_t thread;
  int p = htons(atoi(port));
  pthread_create(&thread, NULL, func_socket,(void *)(long)p);
  pthread_detach(thread);
}

void createPool()
{
  pthread_t thread;
  int i;
  
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond_work, NULL);

  for(i=0;i<POOL_SIZE;i++)
  {
    pthread_create(&thread, NULL, func_main,(void *)(long)i);
    pthread_detach(thread);
  }


}
void *func_socket(void *data)
{
  int port = (int)data;
  int serv_sock, cli_sock, cli_addr_size;

  struct sockaddr_in serv_addr, cli_addr;
  struct task task;

  serv_sock = socket(PF_INET,SOCK_STREAM,0);

  memset(&serv_addr,0,sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = port; 
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))== -1)
  {
    printf("bind error");
    exit(1);
  }

  if(listen(serv_sock, 10)==-1)
  {
    printf("listen error");
    exit(1);
  }

  cli_addr_size = sizeof(cli_addr);

  while(1)
  {
    printf("socket port= %d\n",port);
    cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, (socklen_t *)&cli_addr_size);

    task.sock_num = cli_sock;
    enQueue(queue,task);
  }
}
void *func_main(void *data)
{
  int id = (int)data;
  struct task tmp;
  while(1)
  {
    printf("test%d\n",id);

    //tmp= deQueue(queue);

    //printf("[task_thread%d]socket_num = %d\n",id,tmp.sock_num);
    sleep(5);
  }
}
