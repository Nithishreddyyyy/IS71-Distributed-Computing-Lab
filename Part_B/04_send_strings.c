#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char message[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 4) {
        if (rank == 0) printf("Run with exactly 4 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        for (int source = 1; source <= 3; source++) {
            MPI_Recv(message, 100, MPI_CHAR, source, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("From process %d: %s\n", source, message);
        }
    } else {
        if (rank == 1) strcpy(message, "Bangalore");
        else if (rank == 2) strcpy(message, "Ramaiah Institute of Technology");
        else strcpy(message, "Information Science and Engineering");

        /* Include the terminating null character. */
        MPI_Send(message, (int)strlen(message) + 1, MPI_CHAR,
                 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
