#include <stdio.h>

int main(void)
{
    int N;
    double sum = 0.0;

    printf("Input positive integer:");
    if (scanf("%d", &N) != 1 || N < 0) {
        return 0; 
    }

    // 級数計算
    for (int k = 0; k <= N; k++) {
        if (k % 2 == 0) {               // 偶数項は正の項
            sum += 1.0 / (2 * k + 1);
        } else {
            sum -= 1.0 / (2 * k + 1);   // 奇数項は負の項
        }
    }
    sum *= 4.0;

    // 出力
    printf("Sum is %.10f\n", sum);

    return 0;
}
