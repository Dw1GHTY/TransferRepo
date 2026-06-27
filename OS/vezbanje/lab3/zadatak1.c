#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFF_SIZE 200

char input[BUFF_SIZE];
int process_descriptors1[2]; // 0 - read | 1 - write
int process_descriptors2[2];
int pid1, pid2;

int main(int argc, char *argv[])
{
    if (pipe(process_descriptors1) < 0)
        exit(1);
    if (pipe(process_descriptors2) < 0)
        exit(1);

    if ((pid1 = fork()) != 0)
    {
        // roditelj
        close(process_descriptors1[0]);
        close(process_descriptors2[0]);
        close(process_descriptors2[1]);

        do
        {
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0'; // uklanja '\n' koji fgets ostavi

            write(process_descriptors1[1], input, strlen(input) + 1);
            printf("First process sent input to second process\n");

        } while (strcmp(input, "END") != 0);

        printf("First process received END input\n");
        wait(NULL);
        close(process_descriptors1[1]);
    }
    else
    {
        if ((pid2 = fork()) != 0)
        {
            // dete 1
            char input1[BUFF_SIZE];

            close(process_descriptors1[1]);
            close(process_descriptors2[0]); // samo pisem u pipe 2

            do
            {
                read(process_descriptors1[0], input1, BUFF_SIZE);

                if (input1[0] >= 'a' && input1[0] <= 'z')
                    input1[0] = toupper(input1[0]);

                write(process_descriptors2[1], input1, strlen(input1) + 1);
                printf("Second process sent message to process 3\n");

            } while (strcmp(input1, "END") != 0);

            close(process_descriptors1[0]);
            close(process_descriptors2[1]);
            wait(NULL);
        }
        else
        {
            // dete 2
            char input2[BUFF_SIZE];
            size_t len;

            close(process_descriptors1[0]);
            close(process_descriptors1[1]);
            close(process_descriptors2[1]); // samo citam iz pipe 2

            do
            {
                read(process_descriptors2[0], input2, BUFF_SIZE);

                if (strcmp(input2, "END") == 0)
                    break;

                len = strlen(input2);
                if (len == 0 || input2[len - 1] != '.')
                {
                    input2[len] = '.';
                    input2[len + 1] = '\0';
                }

                printf("Third process received: %s\n", input2);

            } while (strcmp(input2, "END") != 0);

            close(process_descriptors2[0]);
        }
    }

    return 0;
}