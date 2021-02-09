#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_main(void *data);
int done[5];

int main()
{
  pthread_t threads[5];
  int i, thr_id, rc,status;


  for(i=0;i<5;i++)
  {
    done[i] = 0;
    thr_id = pthread_create(&threads[i], NULL, thread_main, (void *)(long)i);
    if(thr_id < 0)
    {
      perror("create thread error");
      exit(0);
    }
  }
  sleep(1);
  for(i=4;i>=0;i--)
  {
    rc = pthread_cancel(threads[i]);
    printf("===========cancel===========\n");
    if(rc == 0)
    {
      rc = pthread_join(threads[i],(void **)&status);
      printf("===========cancel success===========\n");
      if (rc==0)
      {
        printf("Completed join with thread %d status = %d\n",i,status);
      }
      else
      {
        printf("ERROR; return code from pthread_join() is %d, thread %d\n", rc, i);
         			return -1;
      }
    }
  }
  return 0;
}

void *thread_main(void *data)
{
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
  int id,i; 
  double result = 0;
  id = (int)data;

  printf("thread %d,  pid %d\n",id,getpid());
  
  while(!done[id])
  {
    for(i=0;i<1000000;i++)
    {
       result += random(); 
    }
    printf("id = %d, result = %e\n",id,result);
  }
  pthread_exit((void *)0);
}
