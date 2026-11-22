#include <stdio.h>
#include <mpi.h>

int main(int argc, char * argv[]){
    int rank , a[4] = {1,2,3,4} , x, y ;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Scatter(a, 1, MPI_INT,&x,1,MPI_INT,0,MPI_COMM_WORLD);

    y = x*2;
    printf("Process %d received %d\n",rank,x);

    MPI_Gather(&y,1,MPI_INT,a,1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank == 0){
        printf("Gathered Results: ");
        for(int i= 0  ; i < 4 ; i ++) printf("%d",a[i]);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}