#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>


pthread_t t1, t2;
int n;

void *t1_print(void *args)
{

    int limit = *(int *)args;

    for (int i = 0; i < limit; i++)
    {
        if (i % 7 != 0)
        {
            printf("t1 prints regular num: %d\n", i);
        }
    }
    printf("t1 finished printing, exiting\n");
    return NULL;
}
void *t2_print(void *args)
{
    int limit = *(int *)args;

    for (int i = 0; i < limit; i++)
    {
        if (i % 7 == 0)
        {
            printf("t2 prints num dividable by 7: %d\n", i);
        }
    }
    printf("t2 finished printing, exiting\n");
    return NULL;
}

int main(int argc, char *argv[])
{

    n = atoi(argv[1]);
    printf("Number N from command line is: %d\n", n);

    pthread_create(&t1, NULL, t1_print, (void *)&n);
    pthread_create(&t2, NULL, t2_print, (void *)&n);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}