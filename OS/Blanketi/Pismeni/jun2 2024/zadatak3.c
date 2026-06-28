#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGQ_KEY 10102
#define TRUE 1
#define FALSE 0
#define OUTPUT_FILE "rezultati.txt"

// Struktura poruke - umesto char mtext[N] koristimo int,
// jer msgsnd/msgrcv ne zna ni mari za tip, samo kopira msgsz bajtova
// odmah iza mtype polja.
struct mymsgbuf
{
    long mtype; // mora biti long i > 0
    int broj;   // broj koji se prenosi
};

int is_three_digit_number(int value)
{
    if (value >= 100 && value <= 999)
        return TRUE;
    return FALSE;
}

int sum_of_digits(int value)
{
    int sum = 0;
    while (value != 0)
    {
        sum += value % 10;
        value /= 10;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    int input;
    int cpid;
    int msgq_id;
    struct mymsgbuf buf;

    msgq_id = msgget((key_t)MSGQ_KEY, 0666 | IPC_CREAT);
    if (msgq_id == -1)
    {
        perror("Greska prilikom kreiranja reda poruka");
        exit(1);
    }

    if ((cpid = fork()) != 0)
    {
        // ===== PROCES RODITELJ =====
        while (1)
        {
            printf("Unesite broj (0 za izlaz): ");
            scanf("%d", &input);

            if (input == 0)
            {
                // Signaliziramo detetu da treba da prekine
                buf.mtype = 1;
                buf.broj = 0;
                msgsnd(msgq_id, &buf, sizeof(int), 0);
                break;
            }
            else if (is_three_digit_number(input))
            {
                buf.mtype = 1;
                buf.broj = input;
                msgsnd(msgq_id, &buf, sizeof(int), 0);
            }
            else
            {
                printf("Molim Vas unesite samo trocifrene brojeve\n");
            }
        }

        // Roditelj ceka da se dete zavrsi
        wait(NULL);

        // Brisanje reda poruka nakon zavrsetka oba procesa
        msgctl(msgq_id, IPC_RMID, NULL);
    }
    else
    {
        // ===== PROCES DETE =====
        struct mymsgbuf buf1;
        int input1;
        int sum;
        FILE *f;

        f = fopen(OUTPUT_FILE, "w");
        if (f == NULL)
        {
            printf("Greska prilikom otvaranja fajla\n");
            exit(1);
        }

        do
        {
            // Blokirajuce cekanje na poruku (poslednji argument 0)
            msgrcv(msgq_id, &buf1, sizeof(int), 0, 0);
            input1 = buf1.broj;

            if (input1 != 0)
            {
                sum = sum_of_digits(input1);
                fprintf(f, "Broj: %d, zbir cifara: %d\n", input1, sum);
                printf("[DETE] Primljen broj %d, zbir cifara: %d\n", input1, sum);
            }
        } while (input1 != 0);

        fclose(f);
        exit(0);
    }

    return 0;
}