#include <stdio.h>
#include <omp.h>

int main(void) {
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int n = 10;
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    printf("Sum = %d\n", sum);
    return 0;
}
