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
    printf("Copied file named: %s\n", file_name);

    for (int i = 2; i < argc; i++)
    {
        strcat(keywords, argv[i]);
        strcat(keywords, " "); // separator izmedju reci, da bi se mogle razdvojiti na drugoj strani
    }

    printf("Copied to keyword array: %s\n", keywords);

    pipe(pd_12);
    pipe(pd_23);

    if ((cp1 = fork()) == 0)
    {
        // child 1
        char keywords1[100];
        char file_name1[100];
        int found_lines[100];
        FILE *file;
        // setup pipe
        close(pd_12[1]); // only reads from pipe 1
        close(pd_23[0]); // only writes in pipe 2

        read(pd_12[0], file_name1, sizeof(file_name1));
        read(pd_12[0], keywords1, sizeof(keywords1));

        file = fopen(file_name1, "r");
        int i = 1;
        char read_line[100];
        while (!feof(file))
        {
            fgets(read_line, 100, file);    // read the line
        }
    }
    else if ((cp2 = fork()) == 0)
    {
        // child 2

        // setup pipe
        close(pd_12[0]);
        close(pd_12[1]);
        close(pd_23[1]);

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
        write(pd_12[1], file_name, sizeof(file_name)); // send file name to child 1
        write(pd_12[1], keywords, sizeof(keywords));   // send keywords array to child 1

        close(pd_12[1]);
    }

    wait(NULL);
    wait(NULL);

    return 0;
}