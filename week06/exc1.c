#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STRING_SIZE 10
int main() {
    int descriptors[2];
    pipe(descriptors);

    char *buf_send = "HEY THERE";
    char *buf_receive = malloc(sizeof(char) * STRING_SIZE);

    write(descriptors[1], buf_send, STRING_SIZE);
    read(descriptors[0], buf_receive, STRING_SIZE);
    printf("Sent string: %s | Received string: %s", buf_send, buf_receive);
    return 0;
}