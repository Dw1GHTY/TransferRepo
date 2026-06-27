#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int sig) {
    printf("Stiglo je 5 sekundi!\n");
}

void cancel_handler(int sig)
{
    printf("Cancel program signal received, Ctrl+c\n");
}

int main() {
    // signal(SIGALRM, alarm_handler); // registrujemo handler
    signal(SIGINT, cancel_handler);
    // alarm(5);                       // zatraži SIGALRM nakon 5 sek
    // pause();                        // čekaj da signal stigne
    while(1)
    {
        
    }
    printf("Program se nastavlja...\n");
    return 0;
}