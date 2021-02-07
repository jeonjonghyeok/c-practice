#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#define THREAD 10
#define QUEUE 20

struct threadpool_t {
  pthread_mutex_t lock;
  pthread_t *threads;
  int thread_count;
  int queue_size;
};
typedef struct threadpool_t threadpool_t;
struct threadpool_t pool;

threadpool_t *threadpool_create(int thread_count, int queue_size);

pthread_mutex_t lock;


threadpool_t *threadpool_create(int thread_count, int queue_size){
  threadpool_t *pool;
  int i;

}


int main(int argc, char *argv[]){
  
  pthread_mutex_init(&lock, NULL);

  assert((pool = threadpool_create(THREAD, QUEUE)) != NULL);
  fprintf(stderr, "Pool started with %d threads and queue size of %d\n", THREAD, QUEUE);
  



  return 0;
}
