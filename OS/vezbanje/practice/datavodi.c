#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/sem.h>
#include <string.h>

int main()
{
    int pipe_descriptors[2]; // 0 -> read | 1 -> write
    char buff[255];

    if (pipe(pipe_descriptors) < 0)
        exit(1);

    if (fork() == 0)
    {
        // chil writes
        close(pipe_descriptors[0]);
        wait(NULL);
        close(pipe_descriptors[1]);
    }
    else
    {
        // parent reads
        close(pipe_descriptors[1]);
        close(pipe_descriptors[0]);
    }

    return 0;
}