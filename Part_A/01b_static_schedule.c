#include <stdio.h>
#include <omp.h>

int main(void) {
    int n;

    printf("Enter number of iterations: ");
    scanf("%d",&n);

    /* Run with OMP_NUM_THREADS=2 OMP_SCHEDULE=static,2. */
    #pragma omp parallel for schedule(runtime)
    for (int i = 0; i < n; i++) {
        #pragma omp critical
        printf("Thread %d: Iteration %d\n", omp_get_thread_num(), i);
    }

    return 0;
}
