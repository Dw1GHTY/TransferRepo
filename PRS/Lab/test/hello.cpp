#include <mpi.h>
#include <iostream>
#include <stdio.h>

using namespace std;


// Isti proces može imati različite vrednosti za rang (rank) u
// različitim komunikatorima.
int main(int argc, char *argv[])
{
    int myrank, size;   //size odgovara argumentu kolicine procesora kojim se pokrece program

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cout << "\n";
    cout << "Hello world form processor no: " << myrank << " of size: " << size; 
    cout << "\n";

    MPI_Finalize();
    return 0;
}
