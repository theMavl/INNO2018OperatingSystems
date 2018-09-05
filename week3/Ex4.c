#include <stdio.h>
#include <malloc.h>

int partition(int *array, int low, int high) {
    int pivot = array[high];
    int sm = low - 1;
    int tmp;

    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) {
            sm++;
            tmp = array[sm];
            array[sm] = array[j];
            array[j] = tmp;
        }
    }

    tmp = array[sm + 1];
    array[sm + 1] = array[high];
    array[high] = tmp;
    return sm + 1;
}

void quick_sort(int *array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);
        quick_sort(array, low, pivot - 1);
        quick_sort(array, pivot + 1, high);
    }

}

int main() {
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, size);
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

