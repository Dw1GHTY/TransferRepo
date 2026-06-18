#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

#define NUMARGS                                                                                                                                                                                                                                                                                              \
    20 /*Funkcija  prihvata  komandu  i  obradjuje  je.  U  slucaju  da  je  komanda  logout funkcija vraca 1. U svim ostalim slucajevima vraca 0*/ void *obrada(void *arg)                                                                                                                                  \
    {                                                                                                                                                                                                                                                                                                        \
        char *argumenti[20]; /*Ulazni argumenti komande koju je korisnik zadao*/                                                                                                                                                                                                                             \
        int noArgs;          /*Broj  ulaznih  argumenata  komande  koju  je  korisnik zadao*/                                                                                                                                                                                                                \
        int retStatus;       /*Povratna vrednost sa kojom se komanda zavrsila */                                                                                                                                                                                                                             \
        int pid;                                                                                                                                                                                                                                                                                             \
        char *komanda = (char *)arg; /*  Argumenti  komande  se  izdvajaju  kao  tokeni.  Za  izdvajanje  argumenata  se koristi funkcija strtok. */                                                                                                                                                         \
        noArgs = 0;                                                                                                                                                                                                                                                                                          \
        argumenti[noArgs++] = strtok(komanda, " ");                                                                                                                                                                                                                                                          \
        while ((argumenti[noArgs++] = strtok(0, " ")) != NULL)                                                                                                                                                                                                                                               \
        {                                                                                                                                                                                                                                                                                                    \
        }                                                                                                                                                                                                                                                                                                    \
        if (strcmp(komanda, "logout") != 0)                                                                                                                                                                                                                                                                  \
        {                                                                                                                                                                                                                                                                                                    \
            pid = fork();                                                                                                                                                                                                                                                                                    \
            if (pid == 0)                                                                                                                                                                                                                                                                                    \
            {             /* U novom procesu shell izvrsava zadatu komandu odgvarajucom verzijom exec    *  komande. Ukoliko exec komanda vrati neki kod to znaci da je doslo do greske i    *  treba eksplicitno prekinuti novi proces komandom exit.    * U novom procesu shell izvrsava zadatu komandu */ \
                sleep(5); /*Ukoliko  je  na  kraju  komande  zadat  &  treba  ga  ukloniti  iz  vektora argumenata koji se prosledjuj novom procesu*/
if (strcmp(argumenti[noArgs - 2], "&") == 0)
    argumenti[noArgs - 2] = NULL;
execvp(argumenti[0], argumenti);
printf("\nGRESKA PRI IZVRSENJU KOMANDE!\n");
exit(-1);
}
else
{
    if (strcmp(argumenti[noArgs - 2], "&") != 0) /* Ukoliko je poslednji navedeni argument nije & treba sacekati da se novi proces     *  zavrsi pre prikaza prompt-a. */
        wait(&retStatus);
    return 0;
}
}
else return 1;
}

int main(int argc, char *argv[])
{
    int noArgs;
    char command[100];
    char *arguments[MAX_ARGS];

    pthread_t thread;

    printf("mShell> ");
    fgets(command, 100, stdin);

    noArgs = 0;
    arguments[noArgs++] = strtok(command, " ");

    while ((arguments[noArgs++] = strtok(0, " ")) != NULL)
    {
    }

    while (strcmp(command, "exit") != 0)
    {
        pthread_create(&thread, NULL, ExecuteCommand, arguments);
        if (strcmp(arguments[noArgs - 2], "&") != 0)
        {
            arguments[noArgs - 2] = NULL;
            pthread_join(thread, NULL);
        }
    }
}