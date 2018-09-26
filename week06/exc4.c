#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

void handler_SIGKILL() {
    printf("\nI don't know how, but SIGKILL caught!\nExit...\n");
    exit(1);
}

void handler_SIGSTOP() {
    printf("\nI don't know how, but SIGSTOP caught!\nExit...\n");
    exit(1);
}

void handler_SIGUSR1() {
    printf("\nSIGUSR1 caught!\nExit...\n");
    exit(1);
}

int main() {
    signal(SIGKILL, handler_SIGKILL);
    signal(SIGSTOP, handler_SIGSTOP);
    // The above signals can not be caught...

    signal(SIGUSR1, handler_SIGUSR1);

    while (true) {}
    return 0;
}