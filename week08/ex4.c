#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>
#include <sys/resource.h>

int main() {
    struct rusage usage;
    for (int i = 0; i < 10; i++) {
        void *m = malloc(10 * 1024 * 1024);
        memset(m, 0, 10 * 1024 * 1024);
        getrusage(RUSAGE_SELF, &usage);
        printf("%li\n", usage.ru_maxrss);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}