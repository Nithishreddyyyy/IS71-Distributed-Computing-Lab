#include <stdio.h>
#include <mpi.h>
 
int main(int argc, char *argv[]) {
    int rank, num, square;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    num = rank + 1;
    square = num * num;
 
    printf("Process %d: Square = %d\n", rank, square);
 
    MPI_Barrier(MPI_COMM_WORLD);
 
    if (rank == 0)
        printf("All processes synchronized!\n");
 
    MPI_Finalize();
    return 0;
}