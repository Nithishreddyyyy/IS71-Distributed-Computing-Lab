#include <stdio.h>
#include <mpi.h>
 
int main(int argc, char *argv[]) {
    int rank, a[2], x;
    int sum, prod, min, max;
    int asum, aprod, amin, amax;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    if (rank == 0) {
        printf("Enter two numbers: ");
        fflush(stdout);
        scanf("%d %d", &a[0], &a[1]);
    }
 
    MPI_Bcast(a, 2, MPI_INT, 0, MPI_COMM_WORLD);
    x = a[rank];
 
    MPI_Reduce(&x, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&x, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    MPI_Reduce(&x, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&x, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
 
    MPI_Allreduce(&x, &asum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&x, &aprod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    MPI_Allreduce(&x, &amin, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&x, &amax, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
 
    if (rank == 0) {
        printf("\nMPI_Reduce results:\n");
        printf("SUM = %d\n", sum);
        printf("PRODUCT = %d\n", prod);
        printf("MIN = %d\n", min);
        printf("MAX = %d\n", max);
    }
 
    printf("Process %d Allreduce: SUM=%d PRODUCT=%d MIN=%d MAX=%d\n",
           rank, asum, aprod, amin, amax);
 
    MPI_Finalize();
    return 0;
}
