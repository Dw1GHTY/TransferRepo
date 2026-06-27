/*
 * Zadatak 5 - Sinhronizacioni problem Citaoci - Pisci
 *
 * Pristup bazi podataka obavlja se radi upisa i citanja od strane vise
 * procesa (ovde simulirano nitima). U jednom trenutku moze postojati vise
 * procesa koji citaju sadrzaj iz baze podataka procedurom read_database(),
 * ali ako jedan proces upisuje sadrzaj u bazu podataka procedurom
 * write_database(), nijednom drugom procesu nije dozvoljen pristup bazi
 * podataka radi upisa i citanja.
 *
 * Prednost imaju procesi koji citaju sadrzaj, tako da dok god ima procesa
 * koji citaju iz baze podataka, proces koji treba da upisuje podatke mora
 * da ceka. ("Readers preference" varijanta problema citaoci-pisci)
 *
 * Kompajliranje: gcc citaoci_pisci.c -o citaoci_pisci -lpthread
 * Pokretanje:    ./citaoci_pisci
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int A = 0;  /* Globalna promenljiva koja predstavlja bazu podataka */
int N = 0;  /* Globalna promenljiva koja predstavlja brojac citaoca
               koji u datom trenutku koriste bazu podataka */

sem_t mutex_DB;  /* Semafor za ekskluzivni pristup bazi podataka (pisac vs. svi) */
sem_t mutex_N;   /* Semafor za medjusobno iskljucenje pri izmeni brojaca N */

void read_database(int i)
{
    /* Operacija citanja iz baze se simulira stampanjem globalne promenljive A */
    printf("Nit %d je procitala vrednost %d\n", i, A);
    sleep(rand() % 3);
}

void write_database(void)
{
    /* Operacija upisa u bazu se simulira izmenom vrednosti globalne promenljive A */
    printf("Pisac menja vrednost u bazi podataka.\n");
    A = A + rand() % 10;
    sleep(rand() % 5);
}

void *pisac(void *arg)
{
    while (1)
    {
        /* Pristup bazi je smesten u KS */
        sem_wait(&mutex_DB);
        write_database();
        sem_post(&mutex_DB);

        /* Pravi pauzu pre sledeceg pristupa bazi podataka */
        sleep(rand() % 10);
    }
    return NULL;
}

void *citalac(void *arg)
{
    int i;
    i = *((int *)arg);

    while (1)
    {
        /* Promenljivoj N se pristupa u KS */
        sem_wait(&mutex_N);
        /* Povecava se broj citalaca */
        N++;
        /* Prvi citalac zakljucava bazu podataka kako bi spreciо
           pisca da joj pristupa */
        if (N == 1)
            sem_wait(&mutex_DB);
        sem_post(&mutex_N);

        read_database(i);

        /* Promenljivoj N se pristupa u KS */
        sem_wait(&mutex_N);
        /* Smanjuje se broj citalaca */
        N--;
        /* Poslednji citalac otkljucava bazu podataka */
        if (N == 0)
            sem_post(&mutex_DB);
        sem_post(&mutex_N);

        /* Pravi pauzu pre sledeceg pristupa bazi podataka */
        sleep(rand() % 7);
    }
    return NULL;
}

int main(void)
{
    int i;
    int red_br[4];
    /* Identifikatori niti: 4 citaoca + 1 pisac */
    pthread_t niti[5];

    srand(3232234);

    /* Kreiranje i inicijalizacija semafora */
    sem_init(&mutex_N, 0, 1);
    sem_init(&mutex_DB, 0, 1);

    /* Kreiranje citalaca i pisca */
    for (i = 0; i < 4; i++)
    {
        red_br[i] = i;
        pthread_create(&niti[i], NULL, (void *)citalac, (void *)&red_br[i]);
    }

    pthread_create(&niti[4], NULL, (void *)pisac, (void *)NULL);

    /* Ceka se da se niti zavrse (u praksi se ovo nikad ne desava,
       jer sve niti rade u beskonacnoj petlji) */
    for (i = 0; i < 5; i++)
        pthread_join(niti[i], NULL);

    /* Brisanje semafora */
    sem_destroy(&mutex_N);
    sem_destroy(&mutex_DB);

    return 0;
}