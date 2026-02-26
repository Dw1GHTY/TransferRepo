#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define N 5

sem_t semafori[N];
char recenica[] = "Ovo je test za semafore";

typedef struct
{
    char *rec;
    int id;
} ThreadData;

void *print_rec(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    sem_wait(&semafori[data->id]);

    printf("Nit %d: %s\n", data->id, data->rec);

    if (data->id < N - 1)
    {
        sem_post(&semafori[data->id + 1]);
    }

    return NULL;
}

int main()
{
    pthread_t niti[N];
    ThreadData data[N];
    char *token;

    for (int i = 0; i < N; i++)
    {

        sem_init(&semafori[i], 0, (i == 0 ? 1 : 0));
    }

    token = strtok(recenica, " ");
    for (int i = 0; i < N; i++)
    {
        data[i].rec = token;
        data[i].id = i;
        pthread_create(&niti[i], NULL, print_rec, &data[i]);
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(niti[i], NULL);
        sem_destroy(&semafori[i]);
    }

    return 0;
}