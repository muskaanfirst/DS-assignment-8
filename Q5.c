#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void heapify_max(int arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify_max(arr, n, largest);
    }
}

void heapify_min(int arr[], int n, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l] < arr[smallest]) smallest = l;
    if (r < n && arr[r] < arr[smallest]) smallest = r;
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify_min(arr, n, smallest);
    }
}

void heapsort_increasing(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; --i) heapify_max(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(&arr[0], &arr[i]);
        heapify_max(arr, i, 0);
    }
}

void heapsort_decreasing(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; --i) heapify_min(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(&arr[0], &arr[i]);
        heapify_min(arr, i, 0);
    }
}

void print_array(const char *label, int arr[], int n) {
    printf("%s", label);
    for (int i = 0; i < n; ++i) printf("%d%c", arr[i], i+1==n?'\n':' ');
}

int main(void) {
    int a1[] = {12, 11, 13, 5, 6, 7};
    int n1 = sizeof(a1)/sizeof(a1[0]);
    int a2[] = {12, 11, 13, 5, 6, 7};
    int n2 = n1;

    heapsort_increasing(a1, n1);
    print_array("Increasing (ascending): ", a1, n1);

    heapsort_decreasing(a2, n2);
    print_array("Decreasing (descending): ", a2, n2);

    return 0;
}
