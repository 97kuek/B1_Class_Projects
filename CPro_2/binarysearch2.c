#include <stdio.h>
#include <stdlib.h>

#define N 100

// 比較関数
int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

// 二分探索関数
int BinarySearch(int *Data, int n, int key) {
    int left = 0, right = n - 1, ans = -1; 
    while (left <= right) {                     // 探索範囲が有効な間
        int mid = (left + right) / 2;           // 中央のインデックスを計算
        if (Data[mid] == key) {                 // 探索値が中央の値と一致
            ans = mid;
            right = mid - 1;
        }
        else if (Data[mid] > key) {             // 探索値が中央の値より小さい場合
            right = mid - 1;
        }
        else {                                  // 探索値が中央の値より大きい場合 
            left = mid + 1;
        }
    }
    return ans;
}

int main(void) {
    int *Data;
    FILE *file;
    int i, key, idx;

    Data = (int*)malloc(sizeof(int) * N);                           // 動的メモリ確保
    if (Data == NULL) {                                             // メモリ確保失敗
        fprintf(stderr, "cannot allocate memory\n");
        return 1;
    }

    // ファイルオープン
    file = fopen("data.txt", "r");                                  // data.txtを読み取りモードで開く
    if (file == NULL) {                                             // ファイルオープン失敗 
        fprintf(stderr, "cannot open file: %s\n", "data.txt");
        free(Data);
        return 1;
    }

    // データ読み込み
    for (i = 0; i < N; i++) {                                       // data.txtからN個の整数を読み込む
        if (fscanf(file, "%d", &Data[i]) != 1) {                    // 読み込みに失敗した場合
            fprintf(stderr, "read error at index %d\n", i);         // エラーメッセージを表示
            fclose(file);                                           // ファイルを閉じる
            free(Data);                                             // メモリを解放
            return 1;
        }
    }
    fclose(file);                                                   // ファイルを閉じる

    // data.txtの内容をソート
    qsort(Data, N, sizeof(int), cmp_int);

    // 入力ループ
    while (printf("key: "), scanf("%d", &key) == 1) {
        idx = BinarySearch(Data, N, key);
        if (idx == -1) {
            printf("not found.\n");
        } else {
            printf("found. index: %d\n", idx);
        }
    }

    // メモリ解放
    free(Data);
    return 0;
}
