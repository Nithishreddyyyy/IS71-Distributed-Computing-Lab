#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, value = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2) {
        if (rank == 0) printf("Use at least 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        value = 10;
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received %d from process 0\n", value);
    }

    if (rank == 0) value = 100;
    /* All processes must call Bcast, including the root. */
    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d received broadcast value %d\n", rank, value);

    MPI_Finalize();
    return 0;
}
