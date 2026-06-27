#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>

#define N1 10
#define N2 5
#define N3 20

// buffers
int B1[N1], B2[N2], B3[N3];

// free space indicators
int empty1 = N1;
int empty2 = N2;
int empty3 = N3;

// since buffer is FIFO, heads and tails foreach buffer
int head1 = 0;
int tail1 = 0;
int head2 = 0;
int tail2 = 0;
int head3 = 0;
int tail3 = 0;

// mutex semaphores
sem_t mutex_B1, mutex_B2, mutex_B3, mutex_empty;

void *thread0(void *args)
{
    int data;

    while (1)
    {
        sleep(rand() % 3);
        sem_wait(&mutex_empty); // binarni semafor - mutex - kao signal
        printf("Generating data by thread0\n");

        if (empty3 > 0)
        {
            B3[tail3] = rand() % 1000;
            tail3 = (tail3 + 1) % N3;
            empty3--;
            sem_post(&mutex_B3);
            continue;
        }
        else
            sem_post(&mutex_B3);

        sem_wait(&mutex_B1);
        if (empty1 > 0)
        {
            B1[tail1] = rand() % 1000;
            tail1 = (tail1 + 1) % N1;
            empty1--;
            sem_post(&mutex_B1);
            continue;
        }
        else
            sem_post(&mutex_B1);

        sem_wait(&mutex_B2);
        if (empty2 > 0)
        {
            B2[tail2] = rand() % 1000;
            tail2 = (tail2 + 1) % N2;
            empty2--;
            sem_post(&mutex_B2);
            continue;
        }
        else
            sem_post(&mutex_B2);
    }
    return NULL;
}

void *thread1(void *args)
{
    while (1)
    {
        sem_wait(&mutex_B1);
        if (empty1 < N1)
        {
            printf("thread1 has read value from B1: %d ", B1[head1]);
            head1 = (head1 + 1) % N1;
            empty1++;

            sem_post(&mutex_empty);
        }
        sem_post(&mutex_B1);

        sleep(rand() % 5);
    }
    return NULL;
}
void *thread2(void *args)
{
    while (1)
    {
        sem_wait(&mutex_B2);

        if (empty2 < N2)
        {
            printf("thread2 read value form B2: %d ", B2[head2]);
            head2 = (head2 + 1) % N2;
            empty2++;
            sem_post(&mutex_empty);
        }
        sem_post(&mutex_B2);

        sleep(rand() % 3);
    }
    return NULL;
}

void *thread3(void *args)
{
    while (1)
    {
        sem_wait(&mutex_B3);

        if (empty3 < N3)
        {
            printf("thread2 read value form B2: %d", B2[head2]);
            head3 = (head3 + 1) % N3;
            empty3++;
            sem_post(&mutex_empty);
        }
        sem_post(&mutex_B3);
        sleep(rand() % 2);
    }
    return NULL;
}

int main(int arcg, char *argv[])
{
    pthread_t t0, t1, t2, t3;

    srand(3232234); 


    sem_init(&mutex_B1, 0, 1);
    sem_init(&mutex_B2, 0, 1);
    sem_init(&mutex_B3, 0, 1);
    sem_init(&mutex_empty, 0, N1 + N2 + N3);

    pthread_create(&t0, NULL, thread0, NULL);
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&mutex_B1);
    sem_destroy(&mutex_B2);
    sem_destroy(&mutex_B3);
    sem_destroy(&mutex_empty);

    return 0;
}