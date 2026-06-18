#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>

//gcc threads.c -o threads –lpthread

void* print_thread_number(void* arg)
{
    int threadNumber = (int)arg;

    printf("Thread number %d\n", threadNumber);


    return NULL;
}

int main(int argc, char* argv[])
{

    pthread_t thread_handles[3];


    for(int i = 0; i < 3; i++)
    {
        pthread_create(&thread_handles[i], NULL, print_thread_number, (void*)i);
    }

    for(int i = 0; i < 3; i++)
    {
        pthread_join(thread_handles[i], NULL);
    }

    return 0;
}