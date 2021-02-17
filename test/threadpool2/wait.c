#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

int main()
{
  int status;
  pid_t pid, wait_pid;
  pid = fork();

  if(pid == 0)
    printf("child Process pid= %ld\n",(long)getpid());
  else if(pid > 0)
  {
    printf("Parent Process pid= %ld\n",(long)getpid());
    sleep(5);
    wait_pid = wait(&status);
    if(wait_pid == -1)
    {
      printf("error num: %d \n",errno);
      perror("wait error return");
    }
    else {
      if(WIFEXITED(status))
        printf("wait: 자식프로세스 정상 종료 %d\n",WEXITSTATUS(status));
      else if(WIFSIGNALED(status))
        printf("wait: 자식 프로세스 비정상 종료 %d\n",WTERMSIG(status));
    }
    printf("부모 프로세스 종료%d %d \n",wait_pid, WTERMSIG(status));

  }

  return 0;

}
