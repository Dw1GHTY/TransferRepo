#include <mpi.h>

int main(int argc, char *argv[])
{
    int np, rank, ierr;

    ierr = MPI_Init(&argc, &argv);

    if (ierr == MPI_SUCCESS)
    {

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &np);

        MPI_Finalize();
    }
    else
    {
        
    }
}