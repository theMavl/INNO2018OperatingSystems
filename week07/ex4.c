#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>

#define OLD_SIZE 5
#define NEW_SIZE 15

void *realloc(void *ptr, size_t size) {
    if (ptr == NULL)
        return malloc(size);

    void *newPtr = malloc(size);
    newPtr = memcpy(newPtr, ptr, size);
    free(ptr);
    return newPtr;
}

int main() {
    int *a = malloc(sizeof(int) * OLD_SIZE);
    for (int i = 0; i < OLD_SIZE; i++) {
        a[i] = i;
        printf("%d ", a[i]);
    }
    printf("\n");

    a = realloc(a, sizeof(int) * NEW_SIZE);

    for (int i = 0; i < NEW_SIZE; i++)
        printf("%d ", a[i]);
    return 0;
}