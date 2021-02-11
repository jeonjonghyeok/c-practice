#include <stdio.h>
#include "queuelib.h"

int main()
{
  struct task_queue *queue;
  queue = createQueue();
  struct task task, tmptask;
  task.task_num = 10;
  task.sock_num = 10;
  enQueue(queue,task);
  int tmp;
  tmptask = deQueue(queue);
  printf("%d\n",tmptask.task_num);
  


  return 0;
}
