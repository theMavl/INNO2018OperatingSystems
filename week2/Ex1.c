#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int a;
    float aa;
    double aaa;

    a = INT_MAX;
    aa = FLT_MAX;
    aaa = DBL_MAX;

    printf("Sizes:\n%d\n%d\n%d\n\n", (int) sizeof(a), (int) sizeof(aa), (int) sizeof(aaa));
    printf("Values:\n%d\n%f\n%f\n", a, aa, aaa);

    return 0;
}