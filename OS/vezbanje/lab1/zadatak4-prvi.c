#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>

int main(int argc, char *argv[])
{

    printf("num of args: %d\n", argc);
    printf("All arguments:\n");

    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}