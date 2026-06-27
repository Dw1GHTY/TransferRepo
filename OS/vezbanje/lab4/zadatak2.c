#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int ctrl_c_count = 0;


// Ctrl+C signal handler
void ctrl_c_handler(int sig_num)
{
    signal(SIGINT, ctrl_c_handler);
    ctrl_c_count++;

    if(ctrl_c_count >= 5)
    {
        printf("Finally exiting process after 5 ctrl+c's\n");
        exit(0);
        fflush(stdout);
    }
}

// Ctrl+Z signal handler
void suspend_handler(int sig_num)
{
    signal(SIGTSTP, suspend_handler);
    printf("You pressed Ctrl+C %d times\n", ctrl_c_count);
    fflush(stdout);
}

int main()
{

    signal(SIGINT, ctrl_c_handler);
    signal(SIGTSTP, suspend_handler);


    for(;;)
        pause();    
    


    return 0;
}