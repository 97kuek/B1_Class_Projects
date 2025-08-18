#include <stdio.h>
#include <math.h>

// 関数の定義
double func(double x) {
    return x - 1.2 * exp(-x);
}

// 関数の導関数の定義
double dfunc(double x) {
    return 1.0 + 1.2 * exp(-x);
}

int main(void) {
    double x, x_new, error;
    int i, max;

    x = 3.0;                                                // 初期値
    error = 1e-6;                                           // 収束条件
    max = 100;                                              // 最大反復回数

    for (i = 1; i <= max; i++) {                            // 最大反復回数まで繰り返す
        x_new = x - func(x) / dfunc(x);                     // ニュートン法の更新式
        printf("x(%03d) = %+.8f\n", i, x_new);              // 現在の x の値を表示

        if (fabs(x_new - x) < error) {                      // もし収束条件を満たしたならば
            printf("answer = %+.8f\n", x_new);              // 収束した場合の結果表示
            return 0;
        }
        x = x_new;                                          // x を更新
    }

    printf("Not converged within %d iterations.\n", max);   // 収束しなかった場合のメッセージ
    return 0;
}
