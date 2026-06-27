#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void* thread_func(void* arg)
{
    int* threadNo = (int*) arg;
    printf("Thread number: %d", threadNo);
}

int main(int argc, char *argv[])
{
    sem_t mutex;
    sem_t empty;
    sem_t full;





    return 0;
}