#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

char username[40];

void alarm_handler(int sig_num)
{
    printf("30 seconds have passed, YOU HAVE FAILED ME FOR THE LAST TIME ADMIRAL NEEDA\n");
    exit(0);
}

int main()
{
    signal(SIGALRM, alarm_handler);

    printf("Please enter your username, you have 30 seconds to comply . . .:\n");
    fflush(stdout);

    alarm(30);
    fgets(username, sizeof(username), stdin);

    int len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    alarm(0);
    printf("Provided value: %s\n", username);
    return 0;
}