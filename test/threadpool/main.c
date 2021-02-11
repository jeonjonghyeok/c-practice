#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "queuelib.h"
#define POOL_SIZE 10


void createPool();
void *func_main(void *data);

pthread_mutex_t mutex;
pthread_cond_t cond_work;
pthread_cond_t cond_main;



int main()
{
  struct task_queue *queue;
  queue = createQueue();
  createPool();



  while(1)
  {
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond_work);
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }

  return 0;
}

void createPool()
{
  pthread_t thread;
  int i;
  
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond_work, NULL);

  for(i=0;i<POOL_SIZE;i++)
  {
    pthread_create(&thread, NULL, func_main,(void *)i);
    pthread_detach(thread);
  }


}
void *func_main(void *data)
{
  int id = (int)data;
  while(1)
  {
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond_work, &mutex);
    printf("test%d\n",id);
    pthread_mutex_unlock(&mutex);
  }

}
