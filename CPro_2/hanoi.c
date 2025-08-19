#include <stdio.h>

// ハノイ関数の実装
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move the disc from %c to %c.\n", from, to);
        return;
    }
    // 1. n-1枚を補助棒へ
    hanoi(n - 1, from, aux, to);
    // 2. 一番大きい円盤を目的地へ
    printf("Move the disc from %c to %c.\n", from, to);
    // 3. 補助棒のn-1枚を目的地へ
    hanoi(n - 1, aux, to, from);
}

int main() {
    int n;
    printf("How many disks ? ");
    scanf("%d", &n);
    hanoi(n, 'A', 'C', 'B');
    return 0;
}
