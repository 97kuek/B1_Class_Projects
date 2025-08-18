#include <stdio.h>
#include <math.h>

// 関数 f(x) の定義
static double f(double x) {
    double g = x - erf(x) - asinh(x*x*x); // atanの中身
    return cos(x*x) + atan(g);
}

// 二分法実行部分
static double bisect(double a, double b, double eps, int max_iter) {
    double fa = f(a), fb = f(b);
    for (int it = 0; it < max_iter; ++it) {
        double m  = 0.5*(a+b);  // 中点
        double fm = f(m);       // 中点のy座標
        if (fabs(fm) < eps || 0.5*(b-a) < eps) return m;
        // 符号変化をチェック
        if ((fa <= 0 && fm >= 0) || (fa >= 0 && fm <= 0)) {
            b = m; fb = fm;
        } else {
            a = m; fa = fm;
        }
    }
    return 0.5*(a+b); // 収束しなかった場合の近似値
}

int main(void) {
    const double L = -3.0, R = 3.0; // 探索区間
    const int    M = 6000;          // 走査分割数
    const double eps = 1e-10;       // 収束条件
    const int    max_iter = 200;    // 最大反復回数

    double x_prev = L;              // 前回の x 値
    double f_prev = f(x_prev);      // 前回の f(x) 値
    int count = 0;                  // 根のカウント

    /* 走査して符号変化区間を拾い、二分法で各根を求める */
    for (int i = 1; i <= M; ++i) {
        double x = L + (R-L) * (double)i / (double)M;
        double fx = f(x);

        if (f_prev == 0.0) { /* まれに格子点がそのまま根 */
            double root = x_prev;
            printf("Root[%d] = %.15f\n", ++count, root);
        } else if (fx == 0.0 || (f_prev < 0 && fx > 0) || (f_prev > 0 && fx < 0)) {
            /* [x_prev, x] に根あり → 二分法で洗練 */
            double a = x_prev, b = x;
            /* 念のため a<b に整える */
            if (a > b) { double tmp=a; a=b; b=tmp; }
            double root = bisect(a, b, eps, max_iter);

            /* 近接重複の抑制：直前の根との差が小さければスキップ */
            if (count == 0 || fabs(root - L) > 0) {
                if (count == 0 || fabs(root - L) > 0) { /* ダミー条件：何もしない */
                }
            }
            printf("The root is: %.15f\n", root);
        }

        x_prev = x;
        f_prev = fx;
    }
    return 0;
}
