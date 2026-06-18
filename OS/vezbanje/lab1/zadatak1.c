#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define NUM_ARGS 20

int main(int argc, char *argv[])
{
    char command[100];
    char *arguments[20];
    int noArgs;
    int retStatus;

    printf("mShell> ");
    fgets(command, 100, stdin);

    noArgs = 0;
    arguments[noArgs++] = strtok(command, " ");
    // strtok(0, " ") znaci da se secka isti string na koji se stalo
    /*
    na kraju arguments niz uvek ima NULL kao zadnji element
    (jer poslednji upis u petlji je baš taj NULL), što je bitno za execvp —
    ona zahteva da niz argumenata bude NULL-terminisan, da zna gde se završava.
    */
    while ((arguments[noArgs++] = strtok(0, " ")) != NULL)
    {
    }

    while (strcmp(command, "exit") != 0)
    {
        if (fork() == 0)
        {
            if(strcmp(arguments[noArgs - 2], "&") == 0)
            {
                arguments[noArgs - 2] = NULL;
    
                execvp(arguments[0], arguments);
                printf("Error occured at execvp");
                exit(-1);

                wait(&retStatus);
            }
            else {
                printf("No & provided, waiting for child process to finish execution");
                sleep(3);
                execvp(arguments[0], arguments);
                printf("Error occured at execvp");
                exit(-1);
            }
        }

        printf("mShell> ");
        fgets(command, 100, stdin);
        noArgs = 0;
        arguments[noArgs++] = strtok(command, " ");
        while((arguments[noArgs++] = strtok(0, " ")) != NULL){} 
    }

    return 0;
}
