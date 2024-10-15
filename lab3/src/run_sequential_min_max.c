#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
        printf("Executing sequential_min_max\n");
        execvp("./sequential_min_max", argv);
        printf("Done\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Waiting for child process to finish executing\n");
        wait(NULL);
    }

    printf("Done Executing\n");
    return 0;
}