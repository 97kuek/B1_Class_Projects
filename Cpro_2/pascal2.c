#include <stdio.h>
#include <limits.h>

/*  再帰なし：
    C(n,k) が奇数かどうかだけを判定（Lucas の定理, mod 2）
    奇数なら 1, 偶数なら 0 を返す
*/
int cnk_is_odd(int n, int k) {
    /* C(n,k) ≡ 1 (mod 2)  ⇔  (k & (n - k)) == 0 */
    return ((k & (n - k)) == 0);
}

int main(void) {
    int N;
    printf("Input N: ");
    if (scanf("%d", &N) != 1) return 0;

    int rows = 1 << N;   /* 2^N 行 */

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            if (cnk_is_odd(i, j)) {
                printf("* ");
            } else {
                printf("  ");  /* 偶数はスペース2つ */
            }
        }
        printf("\n");
    }
    return 0;
}
