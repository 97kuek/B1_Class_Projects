#include <stdio.h>

int main(void)
{
    int N;
    int sum = 0;

    printf("Input number N: ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        return 0;
    }

    // 1から2Nまでの偶数の和を計算
    for (int i = 2; i <= 2 * N; i += 2) {
        sum += i;
    }

    // 出力
    printf("Answer is %d.\n", sum);

    return 0;
}
