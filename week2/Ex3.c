#include <stdio.h>

void draw(int n) {
    int c = 1;
    for (int i = 0; i < n; i++) {
        for (int j = n - i - 1; j > 0; j--) {
            putchar(' ');
        }
        for (int j = 0; j < c; j++) {
            putchar('*');
        }
        putchar('\n');
        c += 2;
    }
}

int main() {
    int n = 0;
    scanf("%d", &n);
    draw(n);
    return 0;
}

