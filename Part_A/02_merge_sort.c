#include <stdio.h>
#include <omp.h>

void merge(int arr[], int left, int mid, int right) {
    int temp[1000], i=left, j=mid+1, k=0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
    }

    while(i<=mid) temp[k++] = arr[i++];
    while(j<=right) temp[k++] = arr[j++];

    for(i=0; i<k; i++)
        arr[left+i] = temp[i];
}

void merge_sort(int arr[], int left, int right) {
    if(left>=right) return;

    int mid = (left+right)/2;
    merge_sort(arr,left,mid);
    merge_sort(arr,mid+1,right);
    merge(arr,left,mid,right);
}

int main() {
    int arr[]={5,2,1,4,3}, temp[]={5,2,1,4,3};
    int n=5, mid=(n-1)/2;
    double start, serial, parallel;

    start=omp_get_wtime();
    merge_sort(arr,0,n-1);
    serial=omp_get_wtime()-start;

    start=omp_get_wtime();
    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        merge_sort(temp,0,mid);

        #pragma omp section
        merge_sort(temp,mid+1,n-1);
    }
    merge(temp,0,mid,n-1);
    parallel=omp_get_wtime()-start;

    printf("Sequential: ");
    for(int i=0;i<n;i++) printf("%d ",arr[i]);

    printf("\nParallel: ");
    for(int i=0;i<n;i++) printf("%d ",temp[i]);

    printf("\nSerial: %f\nParallel: %f\n",serial,parallel);
    return 0;
}