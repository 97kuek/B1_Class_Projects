#include <stdio.h>
#include <math.h>

#define MAXN 50     // 最大行列サイズ
#define EPS 1e-12   // 特異チェックの閾値

// 行列 A とベクトル b を表示する関数
static void printAb(double A[MAXN][MAXN], double b[MAXN], int N) {
    printf("A, b =\n");
    for (int i = 0; i < N; ++i) {                                   // 各行を表示
        for (int j = 0; j < N; ++j) printf("%6.1f", A[i][j]);       // 行 i の各列を表示
        printf("  |%6.1f\n", b[i]);                                 // 行 i の b[i] を表示
    }
    printf("\n");
}

int main(void) {
    int N;
    double A[MAXN][MAXN], b[MAXN], x[MAXN];

    // 行列のサイズ N の入力
    printf("N = "); if (scanf("%d", &N) != 1 || N <= 0 || N > MAXN) return 0;

    // 行列 A とベクトル b の入力
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &A[i][j]);
        }
    for (int i = 0; i < N; ++i) {
        printf("b[%d] = ", i);
        scanf("%lf", &b[i]);
    }

    // 初期状態の行列 A とベクトル b の表示
    printAb(A, b, N);

    // ガウスの消去法による行列の前進消去と後退代入
    for (int k = 0; k < N; ++k) {
        /* 1) pivot 探索（列 k で最大絶対値の行）*/
        int piv = k;
        double amax = fabs(A[k][k]);
        for (int i = k + 1; i < N; ++i) {
            if (fabs(A[i][k]) > amax) {
                amax = fabs(A[i][k]);
                piv = i;
            }
        }

        /* 2) 行入替え（必要なら）*/
        if (piv != k) {
            for (int j = k; j < N; ++j) {
                double tmp = A[k][j];
                A[k][j] = A[piv][j];
                A[piv][j] = tmp;
            }
            double tmpb = b[k]; b[k] = b[piv]; b[piv] = tmpb;
            printAb(A, b, N);      /* 行入替え直後を表示 */
        }

        /* 特異チェック */
        if (fabs(A[k][k]) < EPS) {
            printf("Singular or nearly singular matrix at column %d.\n", k);
            return 0;
        }

        /* 3) 下三角を 0 にする */
        for (int i = k + 1; i < N; ++i) {
            double m = A[i][k] / A[k][k];
            if (fabs(m) < EPS) continue;
            for (int j = k; j < N; ++j) A[i][j] -= m * A[k][j];
            b[i] -= m * b[k];
        }
        printAb(A, b, N);          /* 列 k の消去後を表示 */
    }

    /* --- 後退代入 --- */
    for (int i = N - 1; i >= 0; --i) {
        double s = b[i];
        for (int j = i + 1; j < N; ++j) s -= A[i][j] * x[j];
        if (fabs(A[i][i]) < EPS) {
            printf("Singular or nearly singular on back-substitution at row %d.\n", i);
            return 0;
        }
        x[i] = s / A[i][i];
    }

    /* 解の表示 */
    printf("solution x =\n");
    for (int i = 0; i < N; ++i) printf("x[%d] = %.10g\n", i, x[i]);

    return 0;
}