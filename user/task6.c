#include "kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"

int main(){

	int p[2];
	char msg[] = "hello from child";
	char buffer[50];
	pipe(p);
	int pid = fork();
	if (pid <0){
	printf("fork faild");
	exit(1);	
	}
	if(pid==0){
	close(p[0]);
	write(p[1], msg, sizeof(msg));
	close(p[1]);
	exit(0);
	}else{
	close(p[1]);
	read(p[0], buffer,sizeof(buffer));
	printf("parent received: %s\n",buffer);
	close(p[0]);
	wait(0);
	}

	exit(0);

}
