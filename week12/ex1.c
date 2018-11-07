#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <malloc.h>


int main() {
    int devrand = open("/dev/random", O_RDONLY);
    if (devrand < 0) {
        return -1;
    } else {
        char *randData = malloc(sizeof(char) * 20);
        if (read(devrand, randData, 20) < 0)
            return -1;
        printf("%s", randData);
    }
    return 0;
}