#include <stdio.h>
#include <math.h>

// 複素数を表す構造体
struct comp {
    double a; // 実部
    double b; // 虚部
};

/* ほぼゼロを 0 に丸めて -0 表示を避ける */
static double z0(double x) { return (fabs(x) < 1e-12) ? 0.0 : x; }

// 複素数の出力関数
void printcomp(struct comp C) {
    C.a = z0(C.a);
    C.b = z0(C.b);
    if (C.b >= 0)
        printf("%g+%gi", C.a, C.b);
    else
        printf("%g-%gi", C.a, -C.b);
}

/*
構造体の関数
struct comp  関数名(引数リスト) {
    // 関数の本体
    // ...
    return 戻り値;  // 必要に応じて戻り値を返す
}

*/

// 複素数の加算
struct comp cadd(struct comp C1, struct comp C2) {
    struct comp R = { C1.a + C2.a, C1.b + C2.b };
    return R;
}

// 複素数の減算
struct comp csub(struct comp C1, struct comp C2) {
    struct comp R = { C1.a - C2.a, C1.b - C2.b };
    return R;
}

// 複素数の乗算
struct comp cmul(struct comp C1, struct comp C2) {
    struct comp R = {
        C1.a * C2.a - C1.b * C2.b,
        C1.a * C2.b + C1.b * C2.a
    };
    return R;
}

// 複素数の除算
struct comp cdiv(struct comp C1, struct comp C2) {
    double den = C2.a * C2.a + C2.b * C2.b;
    struct comp R;
    if (den == 0.0) {   // 0除算
        R.a = NAN;      // Not a Number (NaN) を設定
        R.b = NAN;      // Not a Number (NaN) を設定
    } else {
        R.a = (C1.a * C2.a + C1.b * C2.b) / den;
        R.b = (C1.b * C2.a - C1.a * C2.b) / den;
    }
    return R;
}

int main(void) {
    struct comp C1, C2, C3;

    printf("Input a+bi\n");
    printf("a:");
    if (scanf("%lf", &C1.a) != 1) return 1;
    printf("b:");
    if (scanf("%lf", &C1.b) != 1) return 1;

    printf("Input c+di\n");
    printf("c:");
    if (scanf("%lf", &C2.a) != 1) return 1;
    printf("d:");
    if (scanf("%lf", &C2.b) != 1) return 1;

    C3 = cadd(C1, C2);
    printf("(a+bi)+(c+di)=");
    printcomp(C3);
    printf("\n");

    C3 = csub(C1, C2);
    printf("(a+bi)-(c+di)=");
    printcomp(C3);
    printf("\n");

    C3 = cmul(C1, C2);
    printf("(a+bi)(c+di)=");
    printcomp(C3);
    printf("\n");

    C3 = cdiv(C1, C2);
    printf("(a+bi)/(c+di)=");
    printcomp(C3);
    printf("\n");

    return 0;
}
