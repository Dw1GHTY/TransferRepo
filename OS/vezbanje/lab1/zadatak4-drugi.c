#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <wait.h>
// ovaj program se poziva i prosledjuje mu se ./zadatak4-privi ls . . .
int main(int argc, char *argv[])
{
    char *arguments[20];
    pid_t child_process;

    if (argc <= 1)
        exit(-1);

    for (int i = 1; i < argc; i++)
    {
        arguments[i - 1] = argv[i];
    }

    child_process = fork();

    if (child_process == 0)
    {

        execv(argv[0], arguments);
        printf("Error at execv");
        exit(-1);
    }
    else if (child_process == -1)
    {
        perror("Fork failed");
        exit(-1);
    }

    wait(NULL);

    return 0;
}