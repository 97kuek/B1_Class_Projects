#include <stdio.h>

int main(void)
{
    int N;
    printf("Input N:");
    if (scanf("%d", &N) != 1 || N < 0) {
        return 0;
    }

    // フィボナッチ数列の初項と第2項を定義
    unsigned long long f0 = 0ULL;  // F0
    unsigned long long f1 = 1ULL;  // F1

    for (int i = 0; i <= N; i++) {
        unsigned long long fi;     // Fiを定義
        if (i == 0) {
            fi = f0;               // F0
        } else if (i == 1) {
            fi = f1;               // F1
        } else {
            fi = f0 + f1;          // Fn = F(n-2) + F(n-1)
            f0 = f1;               // F(n-2)を更新
            f1 = fi;               // F(n-1)を更新
        }
        if (i > 0) printf(" ");
        printf("%llu", fi);
    }
    printf("\n");

    return 0;
}
