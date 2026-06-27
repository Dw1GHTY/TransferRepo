#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NO_OF_INPUTS 10

int numbers[NO_OF_INPUTS];      // brojevi koje su niti dobile
int printed[NO_OF_INPUTS] = {0}; // da li je broj na datom indeksu vec odstampan
int numbers_inputted = 0;        // koliko je brojeva do sada uneseno

pthread_mutex_t mutex;
pthread_cond_t unblock_cond;   // signalizira kraj unosa (10 brojeva uneseno)
pthread_cond_t print_cond;     // signalizira da je neka nit odstampala (pa treba opet provjeriti red)

void *print_number(void *args)
{
    int index = *((int *)args); // indeks ove niti u nizovima numbers/printed
    free(args);                 // oslobadjamo memoriju koju je alocirao main za ovaj indeks

    pthread_mutex_lock(&mutex);

    // FAZA 1: cekanje da se unese svih 10 brojeva
    while (numbers_inputted < NO_OF_INPUTS)
    {
        pthread_cond_wait(&unblock_cond, &mutex);
    }

    // FAZA 2: cekanje da dodje red na ovu nit (njena vrednost mora biti
    // trenutni minimum medju jos neodstampanim vrednostima)
    int is_minimum = 0;
    while (!is_minimum)
    {
        is_minimum = 1;
        for (int i = 0; i < NO_OF_INPUTS; i++)
        {
            if (!printed[i] && numbers[i] < numbers[index])
            {
                is_minimum = 0; // postoji neodstampan broj manji od mog
                break;
            }
        }

        if (!is_minimum)
        {
            pthread_cond_wait(&print_cond, &mutex);
        }
    }

    // sada je ova nit na redu
    printf("Broj: %d\n", numbers[index]);
    printed[index] = 1;

    // budimo ostale niti da provere da li je sad neka od njih na redu
    pthread_cond_broadcast(&print_cond);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t threads[NO_OF_INPUTS];
    int i = 0;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&unblock_cond, NULL);
    pthread_cond_init(&print_cond, NULL);

    while (i < NO_OF_INPUTS)
    {
        printf("Enter %d. number:\n", i + 1);
        scanf("%d", &numbers[i]); // broj se odmah upisuje na svoj trajni indeks u nizu

        // svakoj niti prosledjujemo NJENU SOPSTVENU kopiju indeksa,
        // alociranu na heapu, da ne bi sve niti delile istu lokalnu promenljivu
        int *index_copy = malloc(sizeof(int));
        *index_copy = i;

        pthread_create(&threads[i], NULL, print_number, (void *)index_copy);

        pthread_mutex_lock(&mutex);
        numbers_inputted++;
        pthread_mutex_unlock(&mutex);

        i++;
    }

    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&unblock_cond); // svih 10 uneseno - oslobodi cekajuce niti
    pthread_mutex_unlock(&mutex);

    for (i = 0; i < NO_OF_INPUTS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&unblock_cond);
    pthread_cond_destroy(&print_cond);

    return 0;
}