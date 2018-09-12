#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char *cmd = malloc(256 * sizeof(char));
    char *exit = "exit";

    while (1) {
        size_t size = 0;
        printf("$ ");
        getline(&cmd, &size, stdin);
        if (strncmp(cmd, exit, 5) == 0)
            break;
        int PID = fork();
        if (PID == 0) {
            system(cmd);
            return 0;
        }
    }
    return 0;
}