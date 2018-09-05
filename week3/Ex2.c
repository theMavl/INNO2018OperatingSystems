#include <stdio.h>

void bubble_sort(int *arr, int size) {
    int tmp;
    for (int i = 0; i < size; i++) { ;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, size);

    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    return 0;
}

