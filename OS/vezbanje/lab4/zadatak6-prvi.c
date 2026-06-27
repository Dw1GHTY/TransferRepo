#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/msg.h>
#define MSQ_KEY 10102
#define N 100
int msgq_id;
struct mymsgbuf
{
    long mtype;
    char mtext[N];
};
int main(int argc, char *argv[])
{
    FILE *pola1_file;
    char line[N];
    msgq_id = msgget((key_t)MSQ_KEY, 0666 | IPC_CREAT);
    struct mymsgbuf buf;
    strcpy(buf.mtext, "");
    pola1_file = fopen("pola1.txt", "a");
    do
    {
        // FIX: sizeof(buf.mtext) bez +1 -- msgrcv prima KAPACITET bafera, ne duzinu sadrzaja
        msgrcv(msgq_id, &buf, sizeof(buf.mtext), 1, 0);
        strcpy(line, buf.mtext);
        printf("Received message: %s", line);

        // FIX: logika je bila obrnuta (if(strcmp(...)) break; je prekidalo kad NIJE END)
        if (strcmp(line, "END") == 0) break;

        // dodato: konverzija u velika slova pre upisa (deo zadatka)
        for (int j = 0; line[j] != '\0'; j++)
            line[j] = toupper((unsigned char)line[j]);

        fputs(line, pola1_file);
    } while (strcmp(line, "END") != 0);
    printf("Received END indicator, ending execution\n");

    fclose(pola1_file); // dodato: zatvaranje fajla
    msgctl(msgq_id, IPC_RMID, NULL);

    return 0;
}