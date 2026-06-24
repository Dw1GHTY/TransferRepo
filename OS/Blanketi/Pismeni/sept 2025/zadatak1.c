#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>
#include <sys/sem.h>
#include <semaphore.h>
/*
    - Potreban je mutex i uslovna promenljiva
    - Uslov je zbir > 250, kada se ovo uradi, generator ispada iz petlje,
        prakticno mu se salje signal da obustavi
*/

#define N 4

int buffer[N];
int total_sum = 0;

sem_t mutex;
sem_t full;
sem_t empty;

pthread_t generator_thread;

void *generator(void *args)
{
    while (1)
    {
        sleep(rand() % 2);


        sem_wait(&empty);
        sem_wait(&mutex);
        printf("Generator thread created numbers:\n");
        for (int i = 0; i < N; i++){
            buffer[i] = rand() % 9;
            printf("%d ", buffer[i]);
        }
        sem_post(&mutex);
        sem_post(&full);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 1);

    pthread_create(&generator_thread, NULL, generator, NULL);

    do
    {

        sem_wait(&full);        
        sem_wait(&mutex);
        // KS
        for (int i = 0; i < N; i++)
        {
            total_sum += buffer[i];
        }
        printf("Main thread accounted new entries to sum: | %d |\n", total_sum);
        sem_post(&mutex);
        sem_post(&empty);

    } while (total_sum < 250);

    sem_destroy(&mutex);
    sem_destroy(&full);

    return 0;
};