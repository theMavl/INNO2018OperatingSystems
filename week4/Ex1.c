#include <stdio.h>
#include <unistd.h>

int main() {
    int n = 9;
    int PID = fork();
    if (PID >= 0)
        printf("Hello from %s [%d - %d]\n", (PID == 0) ? "child" : "parent", PID, n);
    else
        return -1;
    return 0;
}
