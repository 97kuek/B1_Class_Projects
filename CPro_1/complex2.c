#include <stdio.h>
#include <math.h>

// 複素数の乗算
void cmul(double a, double b, double c, double d, double *x, double *y){
    *x = a*c - b*d;   // 実部
    *y = a*d + b*c;   // 虚部
}

// ほぼゼロを 0 に丸めて -0 表示を避ける
static double z0(double v){ return (fabs(v) < 1e-12) ? 0.0 : v; }

int main(void){
    const double a = 1.0 / sqrt(2.0);   // 実部
    const double b = 1.0 / sqrt(2.0);   // 虚部
    double x = a, y = b;                // z^1 から開始

    for (int k = 1; k < 8; ++k) {       // cmul を7回：z^8 まで
        double nx, ny;
        cmul(x, y, a, b, &nx, &ny);
        x = nx; y = ny;
    }

    x = z0(x); y = z0(y);               // -0 を避ける

    printf("(1/2^(1/2)+1/2^(1/2)i)^8=");
    if (y >= 0)
        printf("%g+%gi\n", x, y);
    else
        printf("%g-%gi\n", x, -y);

    return 0;
}
