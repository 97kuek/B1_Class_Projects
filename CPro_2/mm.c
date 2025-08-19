#include <stdio.h>
#include <stdlib.h>

// 行列を表示する関数
void PrintMatrix(double *A, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%8.1f", A[i*n + j]);                            // A[i][j] の表示 
        printf("\n");
    }
}

// 行列 A と B の積を計算し、結果を C に格納する関数
void Mult_MM(double *A, double *B, double *C, int n) {
    for (int i = 0; i < n; ++i) {                                   // 各行 i に対して
        for (int j = 0; j < n; ++j) {                               // 各列 j に対して
            double s = 0.0;
            for (int k = 0; k < n; ++k) {                           // k は行列の共通次元
                s += A[i*n + k] * B[k*n + j];                       // A[i][k] と B[k][j] の積を加算
            }
            C[i*n + j] = s;                                         // C[i][j] に結果を格納
        }
    }
}

int main(void) {
    int n;
    printf("N= "); if (scanf("%d", &n) != 1 || n <= 0) return 0;

    // 動的メモリ確保
    double *A = (double*)malloc(sizeof(double)*n*n);
    double *B = (double*)malloc(sizeof(double)*n*n);
    double *C = (double*)malloc(sizeof(double)*n*n);
    if (!A || !B || !C) { printf("alloc error\n"); return 1; }

    // 行列 A と B の初期化（例として、A[i][j] = (i+1)*(j+1)）
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            A[i*n + j] = (i+1) * (j+1);
            B[i*n + j] = (i+1) * (j+1);
        }

    // 行列 A と B の表示
    printf("A =\n"); PrintMatrix(A, n);
    printf("\nB =\n"); PrintMatrix(B, n);

    // 行列の積を計算
    Mult_MM(A, B, C, n);

    // 結果の表示
    printf("\nAB =\n"); PrintMatrix(C, n);

    // メモリの解放
    free(A); free(B); free(C);
    return 0;
}
