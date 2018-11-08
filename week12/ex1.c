#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <malloc.h>


int main() {
    int devrand = open("/dev/random", O_RDONLY);
    int out = open("ex1.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (devrand < 0) {
        return -1;
    } else {
        char *randData = malloc(sizeof(char) * 20);
        if (read(devrand, randData, 20) < 0)
            return -1;
        write(out, randData, sizeof(char) * 20);
        close(out);
    }
    return 0;
}