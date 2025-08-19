#include <stdio.h>
#include <math.h>

// 複素数の加算
void cadd(double a, double b, double c, double d, double *x, double *y){
    *x = a + c;
    *y = b + d;
}

// 複素数の減算
void csub(double a, double b, double c, double d, double *x, double *y){
    *x = a - c;
    *y = b - d;
}

// 複素数の乗算
void cmul(double a, double b, double c, double d, double *x, double *y){
    *x = a*c - b*d; // 実部
    *y = a*d + b*c; // 虚部
}

// 複素数の除算
void cdiv(double a, double b, double c, double d, double *x, double *y){
    double den = c*c + d*d;
    if (den == 0.0) {                // 0除算
        *x = NAN;                    // Not a Number (NaN) を設定
        *y = NAN;                    // Not a Number (NaN) を設定
    } else {
        *x = (a*c + b*d) / den;      // 実部
        *y = (b*c - a*d) / den;      // 虚部
    }
}

int main(void){
    double a, b, c, d, x, y;

    printf("Input a+bi\n");
    printf("a:\n");
    scanf("%lf", &a);
    printf("b:\n");
    scanf("%lf", &b);

    printf("Input c+di\n");
    printf("c:\n");
    scanf("%lf", &c);
    printf("d:\n");
    scanf("%lf", &d);

    cadd(a, b, c, d, &x, &y);
    printf("(a+bi)+(c+di)=%f+%fi\n", x, y);

    csub(a, b, c, d, &x, &y);
    printf("(a+bi)-(c+di)=%f+%fi\n", x, y);

    cmul(a, b, c, d, &x, &y);
    printf("(a+bi)(c+di)=%f+%fi\n", x, y);

    cdiv(a, b, c, d, &x, &y);
    printf("(a+bi)/(c+di)=%f+%fi\n", x, y);

    return 0;
}
