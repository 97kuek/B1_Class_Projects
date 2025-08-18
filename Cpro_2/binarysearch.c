#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 500  // 配列の最大長

// IndexedValue 構造体：値と元のインデックスを保持
typedef struct {
    int value;
    int index; 
} IndexedValue;

/* 値で昇順、同値なら index で昇順 */
int compare(const void* a, const void* b) {
    const IndexedValue *x = (const IndexedValue*)a;
    const IndexedValue *y = (const IndexedValue*)b;
    if (x->value != y->value) return x->value - y->value;
    return x->index - y->index;
}

// 初期配列
void init_array(int arr[], int length, int range) {
    for (int i = 0; i < length; i++) arr[i] = rand() % range;
}

// 配列を表示
void print_arr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i % 40 == 0) printf("\n"); // 40個ごとに改行
        printf("%4d", arr[i]);         // 4桁で表示
    }
    printf("\n\n");
}

// 二分探索実行部
// IndexedValue 配列を探索し、値が見つかったら元の配列のインデックスを返す
int binary_search(IndexedValue arr[], int low, int high, int tar) {
    while (low <= high) {                   // 探索範囲が有効な間
        int mid = low + (high - low) / 2;   // 中央のインデックス
        if (arr[mid].value == tar) {        // 探索値が中央の値と一致
            return arr[mid].index; 
        } else if (arr[mid].value < tar) {  // 探索値が中央の値より大きい場合
            low = mid + 1;
        } else {                            // 探索値が中央の値より小さい場合
            high = mid - 1;
        }
    }
    return -1;
}

int main(void) {
    srand(1125);                            // 乱数の初期化
    int range = 1000;                       // 乱数の範囲
    int value;                              // 探索値
    int arr[MAX_LENGTH];                    // 元の配列
    IndexedValue IndexedValues[MAX_LENGTH]; // 値とインデックスを保持する配列

    init_array(arr, MAX_LENGTH, range);     // 配列を初期化

    for (int i = 0; i < MAX_LENGTH; i++) {
        IndexedValues[i].value = arr[i];
        IndexedValues[i].index = i;
    }

    print_arr(arr, MAX_LENGTH);             // 元の配列を表示

    /* 値でソート（元インデックスは保持） */
    qsort(IndexedValues, MAX_LENGTH, sizeof(IndexedValue), compare);

    printf("Enter a value to search: ");    // 入力
    if (scanf("%d", &value) != 1) return 0;

    /* 二分探索 */
    int pos = binary_search(IndexedValues, 0, MAX_LENGTH - 1, value);

    if (pos >= 0) {
        printf("The value %d is located at original index %d\n", value, pos);
    } else {
        printf("The value %d is not found\n", value);
    }

    return 0;
}
