#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main() {
	int fd[2];
	pipe(fd);
	
	int pid = fork();
	
	if (pid <0){
		printf("fork failed\n");
		exit(1);
		}
	if (pid ==0){
		close(fd[1]);

		char buf[50];
		read(fd[0], buf,sizeof(buf));
		printf("childe received : %s\n",buf);
		close(fd[0]);
		}
	else{
		close(fd[0]);
		char msg[] = "hello from parent";
		write(fd[1],msg,sizeof(msg));
		close(fd[1]);
		wait(0);
	}
	exit(0);
  }
