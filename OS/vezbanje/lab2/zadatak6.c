#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/wait.h>

#define MUTEX_KEY 10101
#define PROC_A_KEY 10102
#define PROC_B_KEY 10103

#define LENGTH 20

union semum
{
    int val;
    struct semid_ds *buf;
    short* array;
};

int main(int argc, char *argv[])
{
    int mutex_id, proca_a_id, proc_b_id, retCode;
    union semum semopts;
    struct sembuf sem_lock = {0, -1, 0};
    struct sembuf sem_unlock = {0, 1, 0};

    char line[LENGTH];

    FILE *first_file;
    FILE *second_file;
    FILE *sum_file;

    mutex_id = semget((key_t)MUTEX_KEY, 1, 0666 | IPC_CREAT);
    proca_a_id = semget((key_t)PROC_A_KEY, 1, 0666 | IPC_CREAT);
    proc_b_id = semget((key_t)PROC_B_KEY, 1, 0666 | IPC_CREAT);


    // ovde je sustina, proces a je otkljucan na pocetku a proces b je zakljucan, time se obezbedjuje da je
    // A za neparne linije a B za parne
    semopts.val = 1;
    semctl(mutex_id, 0, SETVAL, semopts);
    semopts.val = 1;
    semctl(proca_a_id, 0, SETVAL, semopts);
    semopts.val = 0;
    semctl(proc_b_id, 0, SETVAL, semopts);



    if (fork() == 0)
    {
        mutex_id = semget((key_t)MUTEX_KEY, 1, 0666);
        proca_a_id = semget((key_t)PROC_A_KEY, 1, 0666);
        proc_b_id = semget((key_t)PROC_B_KEY, 1, 0666);

        first_file = fopen("first.txt", "r");
        while(!feof(first_file))
        {
            fgets(line, LENGTH, first_file);
            semop(proca_a_id, &sem_lock, 1);
            semop(mutex_id, &sem_lock, 1);
            sum_file = fopen("sum.txt", "a");
            fprintf(sum_file, "%s\n", line);
            fclose(sum_file);
            semop(mutex_id, &sem_unlock, 1);
            semop(proc_b_id, &sem_unlock, 1);
        }
        fclose(first_file);
        exit(0);
    }
    else 
    {
        mutex_id = semget((key_t)MUTEX_KEY, 1, 0666);
        proca_a_id = semget((key_t)PROC_A_KEY, 1, 0666);
        proc_b_id = semget((key_t)PROC_B_KEY, 1, 0666);

        second_file = fopen("second.txt", "r");
        while(!feof(second_file))
        {
            fgets(line, LENGTH, second_file);
            semop(proc_b_id, &sem_lock, 1);
            semop(mutex_id, &sem_lock, 1);

            sum_file = fopen("sum.txt", "a");
            fprintf(sum_file, "%s\n", line);
            fclose(sum_file);

            semop(mutex_id, &sem_unlock, 1);
            semop(proca_a_id, &sem_unlock, 1);

        }
        fclose(second_file);
        wait(&retCode);

        semctl(proca_a_id, 0, IPC_RMID, 0);
        semctl(proc_b_id, 0, IPC_RMID, 0);
        semctl(mutex_id, 0, IPC_RMID, 0);

    }
}