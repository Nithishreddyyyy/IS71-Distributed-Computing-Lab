#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, number, square;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 4) {
        if (rank == 0) printf("Run with exactly 4 processes.\n");
        MPI_Finalize();
        return 1;
    }

    number = rank + 1;
    square = number * number;

    /* No process passes this point until all four have finished computing. */
    MPI_Barrier(MPI_COMM_WORLD);
    printf("Process %d after barrier: %d squared = %d\n", rank, number, square);

    MPI_Finalize();
    return 0;
}
