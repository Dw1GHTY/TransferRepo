#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SEM_KEY 10101

int main()
{

    int sem_id;
    struct sembuf sem_lock = {0, -1, NULL};
    union semun semopts;

    sem_id = semget((key_t)SEM_KEY, 1, 0666 | IPC_CREAT);

    if(sem_id < 0){
        perror("Error initializing sys V semaphore");
        exit(1);
    }




    return 0;
}