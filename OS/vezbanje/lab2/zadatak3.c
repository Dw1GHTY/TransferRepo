#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

#define N 20

int num_array[N];

sem_t access_semaphore;
sem_t mutex;

void write_to_array(int value, int position)
{
    num_array[position] = value;
}
int determine_write_delay(int thread_number)
{
    if (thread_number == 1)
        return 2;
    if (thread_number == 2)
        return 4;
    if (thread_number == 3)
        return 8;
}
void print_array()
{
    printf("\n==== BEGIN ARRAY ====\n");
    for (int i = 0; i < N; i++)
    {
        if (num_array[i] == NULL)
        {
            printf(" _ ");
        }
        else
        {
            printf(" %d ", num_array[i]);
        }
    }
    printf("\n==== END ARRAY ====");
}
int determine_position_to_write_at(int thread_number)
{
    int position;
    switch (thread_number)
    {
    case 1:
        position = rand() % 10;
        break;
    case 2:
        position = rand() % 10 + 11;
    case 3:
        position = rand() % 20;
    default:
        break;
    }
}
int random_number() { rand() % 100; }

void *thread_function(void *args)
{
    int thread_number = *((int *)args);
    while (1)
    {
        sleep(determine_write_delay(thread_number));

        if (thread_number == 1 || thread_number == 2)
        {
            sem_wait(&access_semaphore);
            printf("Thread number %d writing: \n", thread_number);
            write_to_array(random_number(), determine_position_to_write_at(thread_number));
            print_array();
            sem_post(&access_semaphore);
        }
        else
        {
            sem_wait(&access_semaphore);
            sem_wait(&access_semaphore);
            sem_wait(&mutex);

            printf("Thread number %d writing: \n", thread_number);
            write_to_array(random_number(), determine_position_to_write_at(thread_number));
            print_array();

            sem_post(&mutex);
            sem_post(&access_semaphore);
            sem_post(&access_semaphore);
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t threads[3];
    sem_init(&access_semaphore, 0, 2);
    sem_init(&mutex, 0, 1);

    // create threads
    for (int i = 1; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, (void *)thread_function, (void *)&i);
    }

    // await thread end
    for (int i = 1; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }
}