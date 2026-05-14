#include "kernel/types.h"
#include "user/user.h"

int main(void) {
    int pid = fork();

    if (pid < 0) {
        printf("fork failed!\n");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        printf("child (pid: %d) executing\n", getpid());
        char *argv[] = {"ls", 0};
        exec("/ls", argv);
        printf("exec failed!\n");
        exit(1);
    } 
    else {
        // Parent process
        int status;
        wait(&status);
        printf("parent (pid %d) waited for child %d, status %d\n", getpid(), pid, status);
        exit(0);
    }
}
