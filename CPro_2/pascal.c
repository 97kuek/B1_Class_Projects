#include <stdio.h>

// 再帰的に二項係数 C(n, k) を計算
int combination(int n, int k) {
    if (k == 0 || k == n) return 1;
    return combination(n - 1, k - 1) + combination(n - 1, k);
}

int main() {
    // 入力
    int N;
    printf("Input N: ");
    scanf("%d", &N);

    int rows = 1 << N;  // 2^N 行
    
    // 出力
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            int val = combination(i, j);
            if (val % 2 == 1) {
                printf("* ");
            } else {
                printf("  ");  // 偶数ならスペース2つ
            }
        }
        printf("\n");
    }

    return 0;
}

