#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <time.h>
int buffer[1];

int main()
{
    int pid;
    int random_number;
    int pd[2];

    srand(time(NULL));

    if (pipe(pd) < 0)
        exit(1);

    if ((pid = fork()) != 0)
    {
        // parent
        int non_even_counter = 0;
        close(pd[0]); // roditelj samo pise u datavod
        buffer[0] = rand() % 100;
        do
        {

            if (buffer[0] % 2 != 0)
            {

                non_even_counter++;
                if (non_even_counter == 3)
                {
                    buffer[0] = -1;
                    write(pd[1], buffer, 4);
                    break;
                }
            }
            else
                non_even_counter = 0;

            write(pd[1], buffer, 4);

            buffer[0] = rand() % 100;

        } while (non_even_counter != 3);

        if (non_even_counter == 3)
        {
            buffer[0] = -1;
            write(pd[1], buffer, 4);
        }

        wait(NULL);
        close(pd[1]);
    }
    else
    {
        // child
        close(pd[1]); // dete samo cita
        int buffer1[1];
        do
        {
            read(pd[0], buffer1, 4);
            
            if(buffer1[0] % 2 == 0)
            {
                printf("Received even number from parent: %d\n", buffer1[0]);
            }
            if(buffer1[0] == -1)
            {
                printf("Parent signaled 3 uneven numbers occured, exiting");
                break;
            }

        } while (buffer1[0] != -1);

        close(pd[0]);
    }

    return 0;
}