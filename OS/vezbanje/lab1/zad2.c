#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <error.h>

#define INPUT_BUFFER 100
#define MAX_ARGS 10

void get_arguments(char *input, char *argv[], int *argc)
{
    int no_of_commands = 0;

    input[strcspn(input, "\n")] = 0;

    char *token = strtok(input, " ");

    while (token != NULL && no_of_commands < MAX_ARGS - 1)
    {
        argv[no_of_commands] = token;
        no_of_commands++;

        token = strtok(NULL, " ");
    }

    argv[no_of_commands] = NULL;
    *argc = no_of_commands;
}
int execute_file(char *batchFile)
{
    FILE *f;
    char command_in_file[100];
    int ret = 0;

    char *argv[] = NULL;
    int argc = 0;
    char *token;

    f = fopen(batchFile, "r");
    if (f != 0)
    {

        while (fgets(command_in_file, 100, f) != NULL)
        {
            command_in_file[strcspn(command_in_file, "\n")] = 0;

            token = strtok(command_in_file, " ");
            while (token != NULL)
            {
                argv[argc] = token;
                argc++;
                token = strtok(command_in_file, NULL);
            }
        }
    }
    fclose(f);
    return 0;
}

int main()
{
    char *shell_label = "my-shell> ";

    char input[INPUT_BUFFER];
    char *token;

    int argc = 0;
    char *argv[MAX_ARGS];
    int process_return_status_code;

    while (1)
    {
        printf("%s", shell_label);
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0)
            break;

        argc = 0;
        token = strtok(input, " ");
        while (token != NULL && argc < MAX_ARGS - 1)
        {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        if (argc == 0)
            continue;

        int background = 0;
        if (strcmp(argv[argc - 1], "&") == 0)
        {
            background = 1;
            argv[argc - 1] = NULL;
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            if (execvp(argv[0], argv) == -1)
            {
                perror("Exec failed");
                exit(-1);
            }
        }
        else if (pid > 0)
        {
            if (!background)
            {
                wait(&process_return_status_code);
            }
            else
            {
                printf("Background PID: %d\n", pid);
            }
        }
    }
    return 0;
}
