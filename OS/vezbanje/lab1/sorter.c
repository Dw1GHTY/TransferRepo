#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

#define MAT_DIM 3

int mat[MAT_DIM][MAT_DIM];

void *sort_row(void *arg)
{
    int row = *((int *)arg);
    printf("Thread will sort row no: %d\n", row);

    for (int i = 0; i < MAT_DIM; i++)
    {
    }

    return NULL;
}

int main()
{

    pthread_t thread_handlers[MAT_DIM];
    int rows[MAT_DIM];

    // input
    for (int i = 0; i < MAT_DIM; i++)
    {
        printf("Unesi %d-tu vrstu:\n", i + 1);

        for (int j = 0; j < MAT_DIM; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    // print
    for (int i = 0; i < MAT_DIM; i++)
    {
        for (int j = 0; j < MAT_DIM; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }

    for (int i = 0; i < MAT_DIM; i++)
    {
        rows[i] = i;
        pthread_create(&thread_handlers[i], NULL, sort_row, (void *)&rows[i]);
    }

    for (int i = 0; i < MAT_DIM; i++)
    {
        pthread_join(thread_handlers[i], NULL);
    }
    return 0;
}