#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) {
        printf("Child process (PID: %d) is running...\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        printf("Parent process (PID: %d) is running...\n", getpid());
        printf("Child process (PID: %d) has been created.\n", pid);

        sleep(30);
        // wait(NULL);

        printf("Parent process (PID: %d) is exiting...\n", getpid());
        exit(EXIT_SUCCESS);
    }

    return 0;
}
