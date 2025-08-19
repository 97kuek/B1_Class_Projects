#include <stdio.h>
#include <math.h>

// 絶対値を計算する関数 myabs
double myabs(double a, double b){
    return sqrt(a*a + b*b);
}

int main(void){
    double a, b;

    printf("Input a+bi\n");
    printf("a: ");
    if (scanf("%lf", &a) != 1) return 1;
    printf("b: ");
    if (scanf("%lf", &b) != 1) return 1;

    double r = myabs(a, b);

    if (b >= 0)
        printf("myabs(%.1f + %.1fi) = %.6f\n", a, b, r);
    else
        printf("myabs(%.1f - %.1fi) = %.6f\n", a, -b, r);

    return 0;
}
