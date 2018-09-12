#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char cmd[256];
    char *exit = "exit";
    while (1) {
        printf("$ ");
        scanf("%s", cmd);
        if (strncmp(cmd, exit, 5) == 0)
            break;
        system(cmd);
    }
    return 0;
}