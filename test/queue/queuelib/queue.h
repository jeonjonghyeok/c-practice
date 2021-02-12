#ifndef __QUEUE_H__
#define __QUEUE_H__
#define MAX_QUEUE_SIZE 5

typedef struct task
{
  int task_num;
  int sock_num;
}task_t;

typedef struct task_queue
{
  int front, rear;
  task_t task[MAX_QUEUE_SIZE];
}task_queue_t;

void enQueue(task_queue_t *q, task_t task);
task_t deQueue(task_queue_t *q);
void createQueue(task_queue_t *q);
int isEmpty(task_queue_t *q);
int isFull(task_queue_t *q);



void print();
#endif




