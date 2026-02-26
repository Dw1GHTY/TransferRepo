#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char* argv[])
{
    int broj_reci = 0;
    char recenica[100] = "Ovo je test za niti";
    char* token;
    
    token = strtok(recenica, " ");
    printf("\n%s\n", token);


    while(token != NULL)
    {
        broj_reci++;
        printf("\n%s\n", token);
        token = strtok(NULL, " ");
    }
}