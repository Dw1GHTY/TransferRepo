#include <mpi.h>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{

    int myrank;
    MPI_Status status;
    int x, y;
    MPI_Init(&argc, &argv);                 /* Initialize MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* Get rank */
    if (myrank == 0)
    {
        x = 3;
        MPI_Recv(&y, 1, MPI_INT, 1, 19, MPI_COMM_WORLD, &status);
        MPI_Send(&x, 1, MPI_INT, 1, 17, MPI_COMM_WORLD);
    }
    else if (myrank == 1)
    {
        x = 5;
        MPI_Send(&x, 1, MPI_INT, 0, 19, MPI_COMM_WORLD);
        MPI_Recv(&y, 1, MPI_INT, 0, 17, MPI_COMM_WORLD, &status);
    }
    printf("Proc % d y = % d", myrank, y);
    MPI_Finalize();

    return 0;
}