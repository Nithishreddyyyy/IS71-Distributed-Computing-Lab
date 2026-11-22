#include <stdio.h>
#include <string.h>
#include <mpi.h>
 
int main(int argc, char *argv[]) {
    int rank;
    char msg[100];
 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    if (rank == 1) {
        char s[] = "Bangalore";
        MPI_Send(s, strlen(s) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    } else if (rank == 2) {
        char s[] = "Ramaiah Institute of Technology";
        MPI_Send(s, strlen(s) + 1, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
    } else if (rank == 3) {
        char s[] = "Information Science and Engineering";
        MPI_Send(s, strlen(s) + 1, MPI_CHAR, 0, 3, MPI_COMM_WORLD);
    } else if (rank == 0) {
        for (int i = 1; i <= 3; i++) {
            MPI_Recv(msg, 100, MPI_CHAR, i, i, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            printf("Process %d sent: %s\n", i, msg);
        }
    }
 
    MPI_Finalize();
    return 0;
}