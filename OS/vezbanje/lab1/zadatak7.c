#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
/*
Korišćenjem  programskog  jezika  C  napisati  Linux  koji  na standardnom izlazu ispisuje proizvoljnu rečenicu
pri čemu svaku reč u rečenici ispisuje posebna nit.
*/
#define MAX_LEN 100

void *print_word(void *arg)
{
    char *word = (char *)arg;
    printf("%s\n", word);
    return NULL;
}

int main(int argc, char *argv[])
{
    // ideja je da kada se pozove program drugi argument bude recenica,
    // u jednoj petlji ce se vrsiti tokenizacija i kreiranje niti i poziv print_word()
    // u drugoj ce se cekati izvrsenje niti
    char *words[20];
    int noOfWords = 0;
    words[noOfWords++] = strtok(argv[1], " ");

    while ((words[noOfWords++] = strtok(0, " ")) != NULL)
    {
    }

    pthread_t threads[noOfWords];
    for(int i = 0; i < noOfWords - 1; i++){
        pthread_create(&threads[i], NULL, print_word, words[i]);
    }

    for(int i = 0; i < noOfWords - 1; i++){
        pthread_join(threads[i], NULL);
    }


    printf("\n");
    return 0;
}