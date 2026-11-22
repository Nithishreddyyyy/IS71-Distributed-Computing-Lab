#include <stdio.h>
#include <omp.h>

int main() {
    int a[] = {1, 100, 123, 21, 13};
    int n = 5;
    int maximum = a[0];

    #pragma omp parallel for reduction(max:maximum)
    for (int i = 0; i < n; i++) {
        if (a[i] > maximum)
            maximum = a[i];
    }

    printf("Maximum = %d\n", maximum);
    return 0;
}
