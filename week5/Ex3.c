#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int count = 0;

int producer_sleep = 0;
int consumer_sleep = 0;

void put_in_buffer() {
    count++;
}

void remove_from_buffer() {
    count--;
}

void *producer_f() {
    while (true) {
        if (producer_sleep == 0) {
            if (count == BUFFER_SIZE) {
                producer_sleep = 1;
                continue;
            }
            put_in_buffer();
            if (count == 1 && consumer_sleep == 1)
                consumer_sleep = 0;
        }
    }

}

void *consumer_f() {
    while (true) {
        if (consumer_sleep == 0) {
            if (count == 0) {
                consumer_sleep = 1;
                continue;
            }
            remove_from_buffer();
            if (count == BUFFER_SIZE - 1 && producer_sleep == 1)
                producer_sleep = 0;
        }
    }
}

int main() {


    pthread_t consumer, producer;
    pthread_create(&consumer, NULL, consumer_f, NULL);
    pthread_create(&producer, NULL, producer_f, NULL);


    while (true) {
        printf("%d\n", count);
        sleep(1);
    }

    return 0;
}