#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
/*
int partition(int arr[], int l, int h) {
    int x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        if(arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[h]);
    return i+1;
} */

int partition(int arr[], int l, int h) {
    int pivot = arr[l];
    int i = l, j = h + 1;
    while (1) {
        while (arr[++i] < pivot) {
            if (i == h) break;
        }
        while (arr[--j] > pivot) {
            if (j == l) break;
        }
        if (i >= j) break;
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[j], &arr[l]);
    return j;
}

// int partition(int arr[], int lo, int hi) {
//     int pivot = arr[lo];
//     int i = lo + 1;
//     int j = hi;
//     while (1) {
//         while (arr[i] < pivot) {
//             i++;
//             if (i == hi) break;
//         }
//         while (arr[j] > pivot) {
//             j--;
//             if (j == lo) break;
//         }
//         if (i >= j) break;
//         swap(&arr[i], &arr[j]);
//     }
//     swap(&arr[j], &arr[lo]);
//     return j;
// }

void quickSortIterative(int arr[], int l, int h) {
    int stack[h - l + 1];
    int top = -1;

    stack[++top] = l;
    stack[++top] = h;

    while (top >= 0) {
        h = stack[top--];
        l = stack[top--];

        int p = partition(arr, l, h);

        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[] = {4, 3, 5, 2, 1, 3, 2, 3};
    int n = sizeof(arr) / sizeof(*arr);
    quickSortIterative(arr, 0, n - 1);
    printArr(arr, n);

    return 0;
}
