#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int count;

void *t_function(void* data)
{
  int num; 
  num = *((int *)data);
  printf("%d\n",num);
  printf("count Before id= %d count= %d\n",num, count);
  count++;
  sleep(1);
  printf("count After id= %d count= %d\n",num, count);
}

int main() 
{
  int a=1;
  int b=2;
  int status;
  int tid;
  pthread_t p_thread[2];

  tid = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
  if(tid < 0)
  {
    perror("create error:");
    exit(0);
  }

  tid = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);
  if(tid < 0)
  {
    perror("create error:");
    exit(0);
  }

  pthread_join(p_thread[0], (void *) &status);
  pthread_join(p_thread[1], (void *) &status);


  return 0;
}
