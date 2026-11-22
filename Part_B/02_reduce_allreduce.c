#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, value, maximum, minimum, sum, product;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /* Product is size factorial; keep it within a 32-bit int. */
    if (size > 12) {
        if (rank == 0) printf("Use at most 12 processes.\n");
        MPI_Finalize();
        return 1;
    }
    value = rank + 1;

    /* Reduce returns the result only at root (rank 0). */
    MPI_Reduce(&value, &maximum, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &minimum, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &product, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("Reduce at root: max=%d min=%d sum=%d product=%d\n",
               maximum, minimum, sum, product);

    /* Allreduce returns the result at every process. */
    MPI_Allreduce(&value, &maximum, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &minimum, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &product, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    printf("Allreduce at process %d: max=%d min=%d sum=%d product=%d\n",
           rank, maximum, minimum, sum, product);

    MPI_Finalize();
    return 0;
}
