/* extrema.c : f'(x)=0 の解（極値）を [-3,3] で全て求める（走査＋二分法） */
#include <stdio.h>
#include <math.h>

/* f(x) */
static double f(double x) {
    double g = x - erf(x) - asinh(x*x*x);
    return cos(x*x) + atan(g);
}

/* f'(x) = -2x sin(x^2) + g'(x)/(1+g(x)^2) */
static double fp(double x) {
    double x2 = x*x;
    double x3 = x2*x;

    double g  = x - erf(x) - asinh(x3);
    double gp = 1.0 - 2.0/sqrt(M_PI)*exp(-x2) - (3.0*x2)/sqrt(1.0 + x3*x3);

    return -2.0*x*sin(x2) + gp / (1.0 + g*g);
}

/* 二分法（f' 用） */
static double bisect_fp(double a, double b, double eps, int max_iter) {
    double fa = fp(a), fb = fp(b);
    for (int it = 0; it < max_iter; ++it) {
        double m  = 0.5*(a+b);
        double fm = fp(m);
        if (fabs(fm) < eps || 0.5*(b-a) < eps) return m;
        if ((fa <= 0 && fm >= 0) || (fa >= 0 && fm <= 0)) {
            b = m; fb = fm;
        } else {
            a = m; fa = fm;
        }
    }
    return 0.5*(a+b);
}

int main(void) {
    const double L = -3.0, R = 3.0;
    const int    M = 6000;        /* 走査分割数 */
    const double eps = 1e-10;     /* 収束条件 */
    const int    max_iter = 200;  /* 反復上限 */

    double x_prev = L;
    double fprev  = fp(x_prev);
    int count = 0;

    for (int i = 1; i <= M; ++i) {
        double x = L + (R-L) * (double)i / (double)M;
        double fx = fp(x);

        if (fprev == 0.0) {
            double xext = x_prev;
            printf("Extrema[%d] x = %.15f, f(x) = %.15f\n", ++count, xext, f(xext));
        } else if (fx == 0.0 || (fprev < 0 && fx > 0) || (fprev > 0 && fx < 0)) {
            double a = x_prev, b = x;
            if (a > b) { double t=a; a=b; b=t; }
            double xext = bisect_fp(a, b, eps, max_iter);
            printf("Extrema[%d] x = %.15f, f(x) = %.15f\n", ++count, xext, f(xext));
        }

        x_prev = x;
        fprev  = fx;
    }

    if (count == 0) {
        printf("No extrema found on [-3,3].\n");
    }
    return 0;
}
