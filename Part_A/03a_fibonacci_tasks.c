#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    int a = 0, b = 1;

    for (int i = 1; i < n; i++) {
        int next = a + b;
        a = b;
        b = next;
    }
    return n == 0 ? 0 : b;
}

int main() {
    int n = 10, arr[47];

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < n; i++) {
                #pragma omp task firstprivate(i)
                arr[i] = fibonacci(i);
            }
            #pragma omp taskwait
        }
    }

    printf("Fibonacci: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
