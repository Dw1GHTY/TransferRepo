#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
    FILE *source_file;
    char line[N];
    struct mymsgbuf buf;
    strcpy(buf.mtext, "");

    msgq_id = msgget((key_t)MSQ_KEY, 0666 | IPC_CREAT);

    source_file = fopen("cela.txt", "r");
    int i = 0;
    while (!feof(source_file))
    {
        i++;

        if (i % 2 != 0)
        {
            // neparni
            buf.mtype = 1;
            fgets(buf.mtext, sizeof(buf.mtext), source_file);
            msgsnd(msgq_id, &buf, strlen(buf.mtext) + 1, 0); // 0 -> blokirajuce
        }
        else
        {
            // parni
            buf.mtype = 2;
            fgets(buf.mtext, sizeof(buf.mtext), source_file);
            msgsnd(msgq_id, &buf, strlen(buf.mtext) + 1, 0); // 0 -> blokirajuce
        }
    }
    if (fork() == 0)
    {
        // dete 1
        execl("zadatak6-prvi", "zadatak6-prvi", NULL);
    }
    else
    {
        if (fork() == 0)
        {
            // dete 2
            execl("zadatak6-drugi", "zadatak6-drugi", NULL);
        }
    }

    // END SIGNAL (not rly signal)
    strcpy(buf.mtext, "END");
    buf.mtype = 1;
    msgsnd(msgq_id, &buf, strlen(buf.mtext) + 1, 0);
    buf.mtype = 2;
    msgsnd(msgq_id, &buf, strlen(buf.mtext) + 1, 0);

    wait(NULL);
    wait(NULL);

    fclose(source_file);
    msgctl(msgq_id, IPC_RMID, NULL);
    return 0;
}