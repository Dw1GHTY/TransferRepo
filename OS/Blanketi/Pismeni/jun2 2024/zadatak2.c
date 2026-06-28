#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>

// child processes
int cp1, cp2;

// pipe descriptor pairs | 0 -> read 1 -> write
int pd_12[2];
int pd_23[2];

int main(int argc, char *argv[])
{
    // main arguments
    char file_name[100]; // argv[1]
    char keywords[100];

    keywords[0] = '\0'; // pocinjemo od praznog stringa, da strcat ima na sta da nadovezuje

    // take in file name
    strcpy(file_name, argv[1]);
    for (int i = 2; i < argc; i++)
    {
        strcat(keywords, argv[i]);
        strcat(keywords, " "); // separator izmedju reci, da bi se mogle razdvojiti na drugoj strani
    }

    pipe(pd_12);
    pipe(pd_23);

    if ((cp1 = fork()) == 0)
    {
        // child 1 - trazi linije u fajlu za svaku kljucnu rec
        char keywords1[100];
        char file_name1[100];
        FILE *file;

        // setup pipe
        close(pd_12[1]); // only reads from pipe 1
        close(pd_23[0]); // only writes in pipe 2

        read(pd_12[0], file_name1, sizeof(file_name1));
        read(pd_12[0], keywords1, sizeof(keywords1));

        printf("\n=== CHILD 1 ===\nChild process received the following through PIPE 1:\n");
        printf("File Name: %s\n", file_name1);
        printf("Keywords: %s\n", keywords1);

        // razdvajanje keywords1 stringa nazad na pojedinacne reci
        // (strcat je u roditelju spojio sve reci u jedan string razdvojen razmacima)
        char *word = strtok(keywords1, " ");
        while (word != NULL)
        {
            file = fopen(file_name1, "r");
            if (file == NULL)
            {
                printf("CHILD 1: Greska pri otvaranju fajla.\n");
                exit(1);
            }

            char read_line[200];
            int line_number = 1;

            while (fgets(read_line, sizeof(read_line), file) != NULL)
            {
                if (strstr(read_line, word) != NULL)
                {
                    printf("CHILD 1: Rec '%s' pronadjena u liniji %d, saljem broj.\n", word, line_number);
                    write(pd_23[1], &line_number, sizeof(int));
                }
                line_number++;
            }

            fclose(file);
            word = strtok(NULL, " "); // sledeca kljucna rec
        }

        // signal kraja - salje se -1 da child2 zna da nema vise podataka
        int end_signal = -1;
        write(pd_23[1], &end_signal, sizeof(int));

        close(pd_23[1]);
    }
    else if ((cp2 = fork()) == 0)
    {
        // child 2 - sabira primljene redne brojeve linija
        int received_number;
        int line_sum = 0;

        // setup pipe
        close(pd_12[0]);
        close(pd_12[1]);
        close(pd_23[1]); // only reads from pipe 2

        while (1)
        {
            read(pd_23[0], &received_number, sizeof(int));

            if (received_number == -1)
            {
                break; // child1 je zavrsio slanje
            }

            line_sum += received_number;
        }

        printf("\n=== CHILD 2 ===\nSum of keyword line findings is: %d\n", line_sum);

        close(pd_23[0]);
    }
    else
    {
        // parent

        // setup pipe
        close(pd_12[0]); // only writes in pipe 1
        close(pd_23[0]); // doesnt use pipe 2 at all
        close(pd_23[1]); // doesnt use pipe 2 at all

        // main parent code
        printf("Parent process sending file named: %s\nand keywords:\n%s\n", file_name, keywords);
        write(pd_12[1], file_name, sizeof(file_name)); // send file name to child 1
        write(pd_12[1], keywords, sizeof(keywords));   // send keywords array to child 1

        close(pd_12[1]);
    }

    wait(NULL);
    wait(NULL);

    return 0;
}