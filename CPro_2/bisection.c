#include <stdio.h>
#include <math.h>

// 関数 f(x) の定義
double func(double x) {
    return x - 1.2 * exp(-x);
}

// 二分法実行部分
double Bisection(double a, double b, double eps) {
    double fa = func(a), fb = func(b), c = 0.0, fc = 0.0;           // 中点とその値
    if (fa * fb >= 0.0) {                                           // f(a) と f(b) が同符号ならば根を持たない
        printf("Error: f(a) and f(b) must have opposite signs.\n"); // エラーメッセージ
        return NAN;                                                 // 根がないので NAN を返す
    }

    while (fabs(b - a) > eps) {                                     // 区間の幅が収束条件より大きい間くりかえす
        c  = 0.5 * (a + b);                                         // 中点の計算
        fc = func(c);                                               // 中点のy座標
        printf("a = %+.6f,  b = %+.6f,  c = %+.6f\n", a, b, c);     // 現在の区間と中点を表示
        if (fa * fc <= 0.0) {                                       // f(a) と f(c) が異符号ならば根は [a, c] にある
            b  = c;
            fb = fc;
        } else {                                                    // f(c) と f(b) が異符号ならば根は [c, b] にある
            a  = c;
            fa = fc;
        }

        if (fabs(fc) <= eps) break;                                 // f(c) が十分小さければ終了
    }
    return 0.5 * (a + b);                                           // 最終的な中点を返す
}

int main(void) {
    double a = 0.0, b = 3.0, eps = 1e-6;    // 初期区間と収束条件
    double ans = Bisection(a, b, eps);      // 二分法実行
    printf("answer = %+.6f\n", ans);      // 結果表示
    return 0;
}
