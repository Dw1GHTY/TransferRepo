#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <wait.h>

#define TRUE 1
#define FALSE 0
#define STR_LEN 50
#define MSGQ_KEY 10102

struct student
{
    int index;
    char first_name[STR_LEN];
    char last_name[STR_LEN];
};

struct mymsgbuf
{
    long mtype;
    struct student data;
};

int main(int argc, char *argv[])
{
    int msgq_id;
    int cpid_1, cpid_2;
    struct mymsgbuf buf;

    msgq_id = msgget((key_t)MSGQ_KEY, 0666 | IPC_CREAT);

    if ((cpid_1 = fork()) == 0)
    {
        // CHILD 1
        FILE *stara_akreditacija;
        int no_of_students1 = 0;
        struct mymsgbuf rcvd1; // <-- MORA biti struct mymsgbuf, ne struct student!

        stara_akreditacija = fopen("stara_akreditacija.txt", "a");
        while (1)
        {
            msgrcv(msgq_id, &rcvd1, sizeof(struct student), 1, 0);
            printf("=== CP1 received message:\n");

            if (rcvd1.data.index == 10000)
                break;
            no_of_students1++;
            fprintf(stara_akreditacija, "%d %s %s\n",
                    rcvd1.data.index, rcvd1.data.first_name, rcvd1.data.last_name);
        }
        fclose(stara_akreditacija);
        printf("Received index 10000, the final number of students is: %d\n", no_of_students1);
    }
    else if ((cpid_2 = fork()) == 0)
    {
        // CHILD 2
        FILE *nova_akreditacija;
        int no_of_students2 = 0;
        struct mymsgbuf rcvd2; // <-- isto, mora biti struct mymsgbuf

        nova_akreditacija = fopen("nova_akreditacija.txt", "a");
        while (1)
        {
            msgrcv(msgq_id, &rcvd2, sizeof(struct student), 2, 0);
            printf("=== CP2 received message:\n");

            if (rcvd2.data.index == 10000)
                break;

            fprintf(nova_akreditacija, "%d %s %s\n",
                    rcvd2.data.index, rcvd2.data.first_name, rcvd2.data.last_name);
            no_of_students2++;
        }

        fclose(nova_akreditacija);
        printf("Received index 10000, the final number of students is: %d\n", no_of_students2);
    }
    else
    {
        struct student input;
        // PARENT
        while (1)
        {
            printf("===== ENTER STUDENT DATA =====\n");
            printf("Enter index:\n");
            scanf("%d", &input.index);
            printf("Enter First Name:\n");
            scanf("%s", input.first_name);
            printf("Enter Last Name:\n");
            scanf("%s", input.last_name);

            if (input.index < 17000)
                buf.mtype = 1; // za cp 1
            else
                buf.mtype = 2; // za cp 2

            buf.data = input;
            msgsnd(msgq_id, &buf, sizeof(struct student), 0);

            if (input.index == 10000)
            {
                // Index 10000 je < 17000, vec poslat Child 1-u iznad.
                // Dodatno obavestavamo Child 2 da prekine.
                buf.mtype = 2;
                msgsnd(msgq_id, &buf, sizeof(struct student), 0);
                break;
            }
        }

        wait(NULL);
        wait(NULL);
        msgctl(msgq_id, IPC_RMID, NULL);
    }

    return 0;
}