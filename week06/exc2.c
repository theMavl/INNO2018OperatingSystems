#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STRING_SIZE 10

int descriptors[2];

int main() {
    pipe(descriptors);
    int PID = fork();

    if (PID == 0) {
        char *buf_receive = malloc(sizeof(char) * STRING_SIZE);
        read(descriptors[0], buf_receive, STRING_SIZE);
        printf("Child received string: %s", buf_receive);
    } else {
        char *buf_send = "OH HI MARK";
        write(descriptors[1], buf_send, STRING_SIZE);
        printf("Parent sent string: %s\n", buf_send);
    }
    return 0;
}