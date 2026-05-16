/*


#include <mpi.h>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
    int myRank, size;
    int dataToSend, receivedData;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    do {
        if (myRank == 0) {
            printf("Enter number: ");
            fflush(stdout);
            scanf("%d", &dataToSend);
            MPI_Send(&dataToSend, 1, MPI_INT, 1, 20, MPI_COMM_WORLD);
        } else {
            MPI_Recv(&receivedData, 1, MPI_INT, myRank - 1, 20, MPI_COMM_WORLD, &status);
            dataToSend = receivedData;
            printf("Process %d received: %d\n", myRank, receivedData);
            fflush(stdout);

            if (myRank < size - 1) {
                MPI_Send(&dataToSend, 1, MPI_INT, myRank + 1, 20, MPI_COMM_WORLD);
            }
        }

    } while ((myRank == 0 ? dataToSend : receivedData) >= 0);

    MPI_Finalize();
    return 0;
}

*/

#include "mpi.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    int rank, value, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    do
    {
        if (rank == 0)
        {
            scanf("%d", &value);
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
            if (rank < size - 1)
                MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
        printf("Process %d got %d\n", rank, value);
    } while (value >= 0);
    MPI_Finalize();
    return 0;
}