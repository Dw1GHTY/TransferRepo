#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define N 4

void *sort_array(void *row)
{
    int *array = (int *)row;
    int tmp;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (array[i] > array[j])
            {
                tmp = array[j];
                array[j] = array[i];
                array[i] = tmp;
            }
        }
    }
    return NULL;
}

void print_matrix(int mat[][N])
{
    printf("\n==== BEGIN PRINT ====\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf(" %d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n==== END PRINT ====\n");
}

void initiate_matrix(int mat[][N])
{
    printf("Create a 4x4 matrix:\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &mat[i][j]);
}

int main(int argc, char *argv[])
{
    int mat[N][N];
    pthread_t threads[N];

    initiate_matrix(mat);
    print_matrix(mat);
    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, sort_array, mat[i]);

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    print_matrix(mat);

    return 0;
}