#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *t_func(void *data);
int done[5];

int main()
{
  int i, rc, status;
  int thr_id;
  pthread_t threads[5];

  printf("pid: %d\n",getpid());

  for(i=0;i<5;i++)
  {
    done[i] = 0;
    thr_id = pthread_create(&threads[i], NULL, t_func, (void *)(long)i);
    if(thr_id < 0)
    {
      perror("create thread error");
      exit(1);
    }  
  }

  for(i=4;i>=0;i--)
  {
    done[i] = 1;
    rc = pthread_join(threads[i], (void **)&status);
    if(rc==0)
    {
      printf("Completed join with thread %d status = %d\n",i,status);
    }
    else
    {
      printf("ERROR; return code from pthread_join() is %d, thread %d\n", rc, i);
      return -1;
    }

  }
  
  return 0;
}

void *t_func(void *data)
{
 int id,pid,i;
 pid = getpid();
 id = (int)data;
 double result=0;
 
 printf("id: %d pid: %d\n",id,pid);

  while(!done[id])
  {
    for(i=0;i<10000;i++)
    {
      result+= random();
    }
    printf("thread %d, result = %e\n",id,result);
  }

 pthread_exit((void *)0);

}
