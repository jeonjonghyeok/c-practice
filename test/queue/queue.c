#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct _task
{
  int task_num;
  int sock_num;
}task_t;

typedef struct _task_queue
{
  int front, rear;
  task_t task[MAX_QUEUE_SIZE]; 
}task_queue_t;

void enQueue(task_queue_t *q, task_t t);
task_t deQueue(task_queue_t *q);
int front = -1,rear = -1;

void enQueue(task_queue_t *q, task_t t)
{
  if(rear > MAX)
  {
    printf("overflow\n");
    exit(1);
  }
  q->rear = q->;
}

task_t deQueue(task_queue_t *q)
{
  if(front == rear)
  {
    printf("underflow\n");
    exit(1);
  }

  return queue[front++];
}

int main()
{
  

}
