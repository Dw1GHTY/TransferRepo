#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#define MAT_DIM 3

void print_mat(int mat[MAT_DIM][MAT_DIM])
{
    for (int i = 0; i < MAT_DIM; i++)
    {
        for (int j = 0; j < MAT_DIM; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void *sortiraj(void *red_matrice)
{
    int *niz = (int *)red_matrice;
    int tmp;

    printf("Prvi element prosledjenog reda matrice: %d\n", niz[0]);

    for (int i = 0; i < MAT_DIM - 1; i++)
    {
        for (int j = 0; j < MAT_DIM - i - 1; j++)
        {
            if (niz[j] > niz[j + 1])
            {
                tmp = niz[j];
                niz[j] = niz[j + 1];
                niz[j + 1] = tmp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int mat[MAT_DIM][MAT_DIM];
    pthread_t niti[MAT_DIM];

    for (int i = 0; i < MAT_DIM; i++)
    {
        for (int j = 0; j < MAT_DIM; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    printf("\n======= Nesortirana matrica =======\n");
    print_mat(mat);

    for (int i = 0; i < MAT_DIM; i++)
    {
        // kreiraj nit
        pthread_create(&niti[i], NULL, (void *)sortiraj, mat[i]);
    }

    for (int i = 0; i < MAT_DIM; i++)
    {
        pthread_join(niti[i], NULL);
    }

    printf("\n======= Sortirana matrica =======\n");
    print_mat(mat);

    return 0;
}
