#include <stdio.h>
#include <stdlib.h>

// A[i][j] を 1次元配列 A[i*n + j] として扱う
// C言語では多次元配列は連続したメモリ領域に格納されるため
// 1次元配列として扱うことで、メモリのアクセスが効率的になるためです。

// 行列を表示する関数
void PrintMatrix(double *A, int n) {
    printf("A =\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%6.1f", A[i*n + j]);                // A[i][j] の表示
        printf("\n");
    }
}

// ベクトルを表示する関数
void PrintVector(double *x, int n) {
    printf("x =\n");
    for (int i = 0; i < n; ++i)
        printf("%6.1f\n", x[i]);                                    // x[i] の表示
}

// 計算実行部
void Mult_MV(double *A, double *x, double *y, int n) {
    for (int i = 0; i < n; ++i) {                                   // 各行 i に対して
        double s = 0.0;
        for (int j = 0; j < n; ++j) {                               // 各列 j に対して
            s += A[i*n + j] * x[j];                                 // A[i][j] と x[j] の積を加算
        }
        y[i] = s;                                                   // y[i] に結果を格納
    }
}

int main(void) {
    int n;
    printf("N= "); if (scanf("%d", &n) != 1 || n <= 0) return 0;    // 行列のサイズ n の入力

    // 動的メモリ確保
    double *A  = (double*)malloc(sizeof(double)*n*n);
    double *x  = (double*)malloc(sizeof(double)*n);
    double *y  = (double*)malloc(sizeof(double)*n);
    if (!A || !x || !y) { printf("alloc error\n"); return 1; }

    // 行列 A とベクトル x の入力
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &A[i*n + j]);
        }
    for (int i = 0; i < n; ++i) {
        printf("x[%d]  = ", i);
        scanf("%lf", &x[i]);
    }

    // 表示と計算
    PrintMatrix(A, n);
    PrintVector(x, n);
    Mult_MV(A, x, y, n);
    printf("Ax =\n");
    for (int i = 0; i < n; ++i) printf("%6.1f\n", y[i]);

    // メモリ解放
    free(A); free(x); free(y);
    return 0;
}
