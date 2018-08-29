#include <stdio.h>

void draw_triangle_1(int n) {
    /*
           *
          ***
         *****
        *******
       *********
     */
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

void draw_triangle_2(int n) {
    /*
       *
       **
       ***
       ****
       *****
     */
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            putchar('*');
        }
        putchar('\n');
    }
}

void draw_triangle_3(int n) {
    /*
      *
      **
      ***
      **
      *
     */

    int middle = n / 2;
    if (n % 2 == 1)
        middle++;
    int direction = 1;
    int is_additional_line_for_even_height_added = 0;

    for (int i = 1; (i <= n && i > 0); i += direction) {
        for (int j = 0; j < i; j++) {
            putchar('*');
        }
        putchar('\n');
        if (i >= middle)
            if (!is_additional_line_for_even_height_added && (n % 2 == 0)) {
                is_additional_line_for_even_height_added = 1;
                i--;
            } else
                direction = -1;
    }
}

void draw_rect(int n) {
    /*
      *****
      *****
      *****
      *****
      *****
     */
    char line[n + 1];

    for (int i = 0; i < n; i++) {
        line[i] = '*';
    }
    line[n] = '\0';
    for (int i = 0; i < n; i++) {
        puts(line);
    }
}


int main() {
    int n = 0;
    scanf("%d", &n);
    draw_triangle_1(n);
    putchar('\n');
    draw_triangle_2(n);
    putchar('\n');
    draw_triangle_3(n);
    putchar('\n');
    draw_rect(n);
    return 0;
}

