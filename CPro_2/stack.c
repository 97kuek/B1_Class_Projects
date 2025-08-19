#include <stdio.h>
#include <stdlib.h>

// (0) malloc を使ったエラー処理付きメモリ確保
void *mallocx(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        printf("cannot allocate memory\n");
        exit(1);
    }
    return p;
}

// (1) typedef を用いたスタック構造体の宣言
typedef struct {
    int Max;        // 最大格納数
    int Count;      // 現在の要素数（次に入る位置）
    double *Data;   // 要素配列
} Stack;

// プロトタイプ
Stack *CreateStack(int size);
void   DisposeStack(Stack *s);
void   PushStack(Stack *s, double x);
double PopStack(Stack *s);
void   PrintStack(const Stack *s);

// (2) スタックを作成する関数
Stack *CreateStack(int size) {
    Stack *s = (Stack *)mallocx(sizeof(Stack));
    s->Max   = size;
    s->Count = 0;
    s->Data  = (double *)mallocx(sizeof(double) * size);
    return s;
}

// 解放
void DisposeStack(Stack *s) {
    if (!s) return;
    free(s->Data);
    free(s);
}

// (3) Push 関数
void PushStack(Stack *s, double x) {
    if (s->Count >= s->Max) {
        printf("stack overflow\n");
        return;
    }
    s->Data[s->Count++] = x;
}

// (4) Pop 関数 
double PopStack(Stack *s) {
    if (s->Count <= 0) {
        printf("stack underflow\n");
        return 0.0;  // エラー時は 0.0 を返す一例
    }
    return s->Data[--s->Count];
}

// 中身表示
void PrintStack(const Stack *s) {
    printf("stack: ");
    if (s->Count == 0) {
        printf("(none)\n");
        return;
    }
    for (int i = 0; i < s->Count; ++i) {
        printf("%.1f", s->Data[i]);
        if (i + 1 < s->Count) printf(", ");
    }
    printf("\n");
}

// 動作確認用メイン
int main(void){
    // 最大格納数 4 でスタックを作成
    Stack *s = CreateStack(4);

    while (1) {
        int cmd;
        PrintStack(s); // スタックの中身表示
        printf("select (1) Push, (2) Pop, (0) Exit: ");
        if (scanf("%d", &cmd) != 1) break;
        if (cmd == 0) break;
        if (cmd == 1) {
            double x;
            printf("input: ");
            if (scanf("%lf", &x) == 1) PushStack(s, x);
        } else if (cmd == 2) {
            double z = PopStack(s);
            printf("output: %.1f\n", z);
        }
    }

    // 後始末
    DisposeStack(s);
    return 0;
}
