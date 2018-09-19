#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 10

void *printer(void *tid) {
    printf("Thread %d started\n", tid);
    printf("Thread %d says some message\n", tid);
    printf("Thread %d exits\n", tid);
    pthread_exit(0);
}

int main() {
    pthread_t threads[N];
    int status;

    printf("\nParallel:\n");
    // Parallel
    for (int i = 0; i < N; i++) {
        printf("Main creates thread %d\n", i);
        status = pthread_create(&threads[i], NULL, printer, (int*)i);
        if (status != 0) {
            printf("Thread %d creation error: %d", i, status);
            exit(-1);
        }
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nSequential:\n");

    // Sequential
    for (int i = 0; i < N; i++) {
        printf("Main creates thread %d\n", i);
        status = pthread_create(&threads[i], NULL, printer, (int*)i);
        pthread_join(threads[i], NULL);
        if (status != 0) {
            printf("Thread %d creation error: %d", i, status);
            exit(-1);
        }
    }

    return 0;
}