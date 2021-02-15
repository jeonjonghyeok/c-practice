#include <stdio.h>
#include <unistd.h>

void masterProcess();

int main()
{
  pid_t pid;
  pid = fork();

  if(pid > 0)
    printPpid();
  else if(pid == 0)
    masterProcess();
  else
  {
    printf("fork fail\n");
    return -1;
  }
  return 0;
}

void masterProcess()
{
  printf("PPID : %ld \n",(long)getpid());
}
