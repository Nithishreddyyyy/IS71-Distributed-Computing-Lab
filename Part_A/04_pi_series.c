#include <stdio.h>
#include <omp.h>

int main(void) {
    int n;
    double sum = 0.0, sign = 1.0, start, serial, parallel, serial_pi;

    printf("Enter number of terms: ");
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    /* Leibniz series: pi = 4 * (1 - 1/3 + 1/5 - 1/7 + ...). */
    start = omp_get_wtime();
    for (int k = 0; k < n; k++) {
        sum += sign / (2.0 * k + 1.0);
        sign = -sign;
    }
    serial_pi = 4.0 * sum;
    serial = omp_get_wtime() - start;

    sum = 0.0;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (int k = 0; k < n; k++) {
        /* Compute sign from k to remove the loop-carried dependency. */
        double term_sign = (k % 2 == 0) ? 1.0 : -1.0;
        sum += term_sign / (2.0 * k + 1.0);
    }
    double parallel_pi = 4.0 * sum;
    parallel = omp_get_wtime() - start;

    printf("Serial pi   = %.12f\n", serial_pi);
    printf("Parallel pi = %.12f\n", parallel_pi);
    printf("Serial time = %.9f s\n", serial);
    printf("Parallel time = %.9f s\n", parallel);
    return 0;
}
