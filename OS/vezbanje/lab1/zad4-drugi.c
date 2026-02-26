#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 20
#define MAX_ARG_LENGTH 100

int main(int argc, char* argv[])
{
    int i;
    char* argumenti[MAX_ARGS];

    //naziv programa koji se poziva, uvek je prvi arg ime tog prog
    argumenti[0] = (char*)malloc(MAX_ARG_LENGTH * sizeof(char));
    strcpy(argumenti[0], "zad4-prvi");

    // uzimanje ostalih argumenata
    for(int i = 1; i < argc; i++)
    {
        argumenti[i] = (char*)malloc(MAX_ARG_LENGTH * sizeof(char));
        strcpy(argumenti[i], argv[i]);
    }
    argv[argc] = NULL;

    if(fork() == 0)
    {
        if(execv("./zad4-prvi", argumenti) < 0)
        {
            printf("Greska u drugom koji izvrsava prvi");
            exit(1);
        }
    }
    else 
    {
        wait(NULL);
    }
    for(int i = 0; i < argc; i++)
    {
        free(argumenti[i]);
    }
    
    return 0;
}