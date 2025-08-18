#include <stdio.h>

// 出力関数
void PrintData(double *Data, int N) {
    for (int i = 0; i < N; ++i) {
        printf("%.0f,", Data[i]);
    }
    printf("\n");
}

// swap 関数
void swap(double *x, double *y) {
    double t = *x; *x = *y; *y = t;
}

// クイックソートの実装
void QuickSortBase(double *Data, int L, int R) {
    int i = L, j = R;
    int p = (L + R) / 2;                                                                // ピボットのインデックスを配列の中心にする
    double pivot = Data[p];                                                             // ピボット値を取得 

    printf("sorting [%d] ... [%d], pivot=[%d]:%.0f\n", L, R, p, pivot);
    while (i <= j) {                                                                    // i と j が交差するまで繰り返す
        while (Data[i] < pivot) i++;                                                    // i を右に進めてピボットより大きい値を探す
        while (Data[j] > pivot) j--;                                                    // j を左に進めてピボットより小さい値を探す
        if (i <= j) {
            if (i != j) {                                                               // i と j が異なる場合のみ交換
                printf("swapped [%d]:%.0f <=> [%d]:%.0f\n", i, Data[i], j, Data[j]);    // i と j の値を表示 
                swap(&Data[i], &Data[j]);                                               // i と j の値を交換
            }
            i++; j--;                                                                   // i を右に、j を左に進める
        }
    }
    if (L < j) QuickSortBase(Data, L, j);                                               // j の左側を再帰的にソート
    if (i < R) QuickSortBase(Data, i, R);                                               // i の右側を再帰的にソート
}

// クイックソートのエントリポイント
void QuickSort(double *Data, int N) {
    if (N >= 2) QuickSortBase(Data, 0, N - 1);
}

int main(void) {
    double Data[] = { 1, 3, 4, 3, 5, 5, 2, 4 };      // ソート対象のデータ
    int N = (int)(sizeof(Data) / sizeof(Data[0]));   // データの個数

    PrintData(Data, N);                              // ソート前の配列を表示
    QuickSort(Data, N);                              // ソート
    PrintData(Data, N);                              // ソート後の配列を表示

    return 0;
}
