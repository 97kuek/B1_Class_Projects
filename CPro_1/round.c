#include <stdio.h>
#include <math.h>

int main(void)
{
    double x;
    int r;

    printf("Input a real number: ");
    if (scanf("%lf", &x) != 1) {
        return 0;
    }

    // round関数を使って四捨五入
    // roundは小数点以下0.5以上で切り上げ、0.5未満で切り捨て
    r = (int)round(x);

    printf("The nearest integer: %d\n", r);
    return 0;
}
