#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_signal(int sig_number)
{
    signal(SIGINT, SIG_DFL);
    printf("Cannot end program");
    fflush(stdout);
}

int main()
{
    signal(SIGINT, handle_signal);

    for(;;)
        pause();

    return 0;
}