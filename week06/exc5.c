#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    int PID = fork();

    if (PID == 0) {
        printf("Created child\n");
        while (1) {
            printf("I'm alive\n");
            fflush(stdout);
            sleep(1);
        }
    } else {
        sleep(10);
        kill(PID, SIGTERM);
        printf("\n**Killed child**\n");
        exit(0);
    }
}
