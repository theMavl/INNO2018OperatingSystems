#include <stdio.h>
#include <memory.h>

int main() {
    char line[100];
    gets(line);
    size_t len = strlen(line);

    for (int i = len-1; i >= 0; i--)
        putchar(line[i]);
    return 0;
}