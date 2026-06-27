#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#include <string.h>

#define MSGQ_KEY 10104
#define MSGLEN 50

int msgq_id;
int cpid;

struct mymsgbuf {
    long mtype;
    char mtext[MSGLEN];
};


int main(int argc, char *argv[])
{
    struct mymsgbuf buf;
    strcpy(buf.mtext, "");   // inicijalizacija PRE fork()-a

    msgq_id = msgget((key_t)MSGQ_KEY, 0666 | IPC_CREAT);

    if ((cpid = fork()) == 0)
    {
        // dete
        struct mymsgbuf buf1;
        strcpy(buf1.mtext, "");

        while(strcmp(buf1.mtext, "QUIT") != 0)
        {
            msgrcv(msgq_id, &buf1, MSGLEN, 0, 0);

            int len = strlen(buf1.mtext);
            if (len > 0 && buf1.mtext[len - 1] == '\n')
                buf1.mtext[len - 1] = '\0';

            printf("Took out message from message queue %d: %s\n", msgq_id, buf1.mtext);
        }
    }
    else
    {
        // roditelj
        while(strcmp(buf.mtext, "QUIT") != 0)
        {
            printf("Enter message to send child process:\n");
            fgets(buf.mtext, sizeof(buf.mtext), stdin);

            // uklanjanje newline-a koji fgets ostavlja na kraju
            int len = strlen(buf.mtext);
            if (len > 0 && buf.mtext[len - 1] == '\n')
                buf.mtext[len - 1] = '\0';

            msgsnd(msgq_id, &buf, strlen(buf.mtext) + 1, 0);
        }

        wait(NULL);
        msgctl(msgq_id, IPC_RMID, NULL);
    }

    return 0;
}