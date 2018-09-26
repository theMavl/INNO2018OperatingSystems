#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>

int main() {
    int FORK1;
    int FORK2;

    int file_descriptors[2];
    if (pipe(file_descriptors) < 0)
        exit(-1);

    FORK1 = fork();

    if (FORK1 != 0) {
        // Still parent
        FORK2 = fork();
        if (FORK2 != 0) {
            // Still parent
            printf("PARENT[%d] | FORK1: %d, FORK2: %d\n", getpid(), FORK1, FORK2);
            write(file_descriptors[1], &FORK2, sizeof(FORK2));
            printf("PARENT[%d] | Write to pipe: %d\n", getpid(), FORK2);
            fflush(stdout);
            int status;
            int p = waitpid(FORK2, &status, WUNTRACED);
            printf("PARENT[%d] | %d terminated with status %d\n", getpid(), p, status);
        } else {
            // FORK2 process
            printf("FORK2[%d] | Started\n", getpid());
            fflush(stdout);
            while (1) {
                printf("FORK2[%d] | Working...\n", getpid());
                fflush(stdout);
                sleep(1);
            }
        }
    } else {
        // FORK1
        printf("FORK1[%d] | Started\n", getpid());
        int received_pid;
        read(file_descriptors[0], &received_pid, sizeof(int));
        printf("FORK1[%d] | Read from pipe: %d\n", getpid(), received_pid);
        fflush(stdout);
        sleep(3);
        kill(received_pid, SIGSTOP);
        printf("FORK1[%d] | killed %d\n", getpid(), received_pid);
        fflush(stdout);
    }
    return 0;
}