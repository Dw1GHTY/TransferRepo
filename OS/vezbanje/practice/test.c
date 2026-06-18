#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    char command[] = "ls";
    printf("Forst process with id: %d\n", getpid());

    pid_t child_process = fork();

    if (child_process != 0)
    {
        printf("Parent: %d\n", getpid());
    }
    else
    {
        printf("Child: %d\n Executing system call now:\n", getpid());
    }

    return 0;
}