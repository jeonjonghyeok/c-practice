#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "queue.h"
#include <arpa/inet.h>
#include <string.h>
#include <sys/wait.h>
#define POOL_SIZE 3 
#define BUF_SIZE 100


void createPool();
void *func_main(void *data);
void *func_socket(void *data);
void createSocketThread(char *port);

pthread_mutex_t mutex;
pthread_cond_t cond_work;
pthread_cond_t cond_main;

struct task_queue queue;
  int serv_sock, cli_sock, cli_addr_size;
  struct sockaddr_in serv_addr, cli_addr;

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    printf("./main port");
    exit(1);

  }

  createSocketThread(argv[1]);
  createQueue(&queue);
  createPool();
  int a;
  scanf("%d",&a);

  return 0;
}

void createSocketThread(char *port)
{
  pthread_t thread;
  int p = htons(atoi(port));
  pthread_create(&thread, NULL, func_socket,(void *)(long)p);
  pthread_detach(thread);


  serv_sock = socket(PF_INET,SOCK_STREAM,0);
  memset(&serv_addr,0,sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = p; 
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
  struct task task;
  int id = (int)data;
  while(1)
  {
    cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, (socklen_t *)&cli_addr_size);
    if(cli_sock == -1)
      continue;
    printf("[%d]socket call, cli[%d]\n",id, cli_sock);

    task.sock_num = cli_sock;
    enQueue(&queue,task);
  }
  close(serv_sock);
  close(cli_sock);
}
void *func_main(void *data)
{
  int id = (int)data;
  struct task tmp;
  char buf[BUF_SIZE];
  while(1)
  {
    pthread_mutex_lock(&mutex);
    if(isEmpty(&queue))
    {
      pthread_mutex_unlock(&mutex);
      continue;
    }
    else
    {
      printf("thread%d work start\n",id);
      tmp= deQueue(&queue);
      pthread_mutex_unlock(&mutex);
      printf("[task_thread%d]socket_num = %d\n",id,tmp.sock_num);
      read(tmp.sock_num,buf,sizeof(buf));

      printf("[task_thread%d]buf=%s\n",id,buf);

      sleep(30);
      write(tmp.sock_num,buf,sizeof(buf));
      printf("thread%d work done!\n",id);
    }
  }
}
