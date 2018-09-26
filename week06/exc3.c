#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

void handler() {
    printf("\nCTRL+C caught!\nExit...\n");
    exit(1);
}

int main() {
    struct sigaction new_handler;
    new_handler.sa_handler = handler;
    sigemptyset(&new_handler.sa_mask);

    // signal(SIGINT, handler);

    sigaction(SIGINT, &new_handler, NULL);
    while (true) {}
    return 0;
}