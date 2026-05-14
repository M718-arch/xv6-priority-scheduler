#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void cpu_work(int n) {
  volatile int x = 0;
  for(int i = 0; i < n * 1000000; i++)
    x++;
}

int
main(void)
{
  int priorities[5] = {5, 4, 3, 2, 1};

  printf("schedtest: starting 5 processes\n");
  printf("priority 1 = highest, priority 5 = lowest\n");
  printf("expected finish order: priority 1 first, priority 5 last\n\n");

  for(int i = 0; i < 5; i++){
    int pid = fork();
    if(pid == 0){
      volatile int x = 0;
      for(int j = 0; j < 100000; j++) x++;
      printf("  started: pid=%d priority=%d\n", getpid(), getpriority(getpid()));
      cpu_work(10);
      printf("  finished: pid=%d priority=%d\n", getpid(), getpriority(getpid()));
      exit(0);
    }
    setpriority(pid, priorities[i]);
  }

  for(int i = 0; i < 5; i++)
    wait(0);

  printf("\nAll done.\n");
  exit(0);
}
