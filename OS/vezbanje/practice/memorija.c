
#include <stdlib.h>


int main()
{
    struct osoba
    {
        char ime[10];
        char prezime[15];
        int godine;
    };
    
    struct osoba *c;

    c = (struct osoba *)malloc(sizeof(struct osoba));

    
    if (c == 0)
    {
        printf("Doslo je do greske");
        exit(1);
    }

    c->ime = "Janko";
    c->prezime = "Janković";
    c->godine = 10;
    free((char *)c);
}