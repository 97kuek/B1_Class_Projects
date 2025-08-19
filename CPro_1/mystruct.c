// mystruct.c
#include <stdio.h>

// 複素数を表す構造体
struct comp {
    double a;                               // 実部
    double b;                               // 虚部
};

// 出力関数
void printcomp(struct comp C) {
    if (C.b >= 0)                           // 虚部が正なら
        printf("%g+%gi", C.a, C.b);         // 実部と虚部を表示
    else                                    // 虚部が負なら
        printf("%g-%gi", C.a, -C.b);        // 実部と虚部を表示（負の符号をつける）
}

int main(void) {
    struct comp C;

    printf("Input a+bi\n");
    printf("a:");
    if (scanf("%lf", &C.a) != 1) return 1;  // 実部が正しく読み込めなければ終了

    printf("b:");
    if (scanf("%lf", &C.b) != 1) return 1;  // 虚部が正しく読み込めなければ終了

    printf("a+bi=");
    printcomp(C);
    printf("\n");

    return 0;
}
