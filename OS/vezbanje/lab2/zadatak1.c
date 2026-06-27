#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NO_OF_WORDS 5
char sentence[NO_OF_WORDS][100] = {"Ovo", "je", "test", "za", "semafore"};
int word_indexes[NO_OF_WORDS];
sem_t sems[NO_OF_WORDS - 1];

void *print_word(void *arg)
{
    int index = *((int *)arg);

    // index > 0 | ukazuje na to da prvi index ne ceka nikoga
    if (index > 0)
        sem_wait(&sems[index - 1]);
    
    printf("%s\n", sentence[index]);

    // index < 4 | s obzirom da je posle wait i print, znaci da kada zavrsi oslobadja svoj semafor
    if (index < 4)
        sem_post(&sems[index]);

    return NULL;
}

int main(int agrc, char *argv[])
{
    pthread_t threads[NO_OF_WORDS];

    for (int i = 0; i < NO_OF_WORDS - 1; i++)
    {
        sem_init(&sems[i], 0, 0);
    }

    for (int i = 0; i < NO_OF_WORDS; i++)
    {
        word_indexes[i] = i;
        pthread_create(&threads[i], NULL, print_word, (void *)&word_indexes[i]);
    }

    for (int i = 0; i < NO_OF_WORDS - 1; i++)
    {
        sem_destroy(&sems[i]);
    }

    for (int i = 0; i < NO_OF_WORDS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
