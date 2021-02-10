#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef struct _task_t
{
  int task_num;
  int sock_num;
}task_t;

typedef struct _task_queue_t
{
  int front, rear;
  task_t task[MAX_QUEUE_SIZE];
}task_queue_t;

void enQueue(task_t task);
task_t deQueue();
int isFull();
int isEmpty();
void queueInit();

task_queue_t queue;

int main()
{
  int i;
  printf("queue test\n");

  task_t tasks[10];
  for(i=0;i<10;i++)
  {
    tasks[i].task_num = i;
    tasks[i].sock_num = i;
  }
  queueInit();

  enQueue(tasks[0]);



  return 0;
}
void enQueue(task_t task)
{
  if(queue.rear == -1)
  {
    queue.task[queue.front] = task; 
    queue.rear = queue.front;
    return;
  }
  if((queue.rear+1)%MAX_QUEUE_SIZE == queue.front)
  {
    printf("this is overflow\n");
    return;
  }
  queue.task[queue.rear+1] = task; 
  queue.rear = (queue.rear+1)%MAX_QUEUE_SIZE;
}

task_t deQueue()
{
  task_t task;
  if(queue.rear== -1)
  {
    printf("this is underflow\n");
    exit(1);
  }
  if(queue.front == queue.rear)
  {
    queue.rear = -1;
    return queue.task[queue.front];
  }


  task = queue.task[queue.front];
  queue.front = (queue.front+1)%MAX_QUEUE_SIZE;
  return task;

}

void queueInit()
{
  queue.front = 0;
  queue.rear = -1;
}


