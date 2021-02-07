#include <stdio.h>
#include <pthread.h>


pthread_mutex_t mutx;

int main(int argc, char **argv){

  pthread_mutex_init(&mutx, NULL);
  
  pthread_mutex_lock(&mutx);




  return 0;
}

