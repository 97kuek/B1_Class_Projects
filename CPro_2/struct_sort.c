#include <stdio.h>
#include <stdlib.h>

#define N 20
#define SEED 123

// 学生の情報を格納する構造体
struct student {
    int No;            // 学籍番号（1..N)
    int Math;          // 数学の点数（0..100）
    int Phy;           // 物理の点数（0..100） 
}; 

// 比較関数（Math 昇順、同点なら No 昇順）
int mathsort(const void *X, const void *Y) {
    const struct student *a = (const struct student *)X;
    const struct student *b = (const struct student *)Y;
    if (a->Math != b->Math) return a->Math - b->Math;
    return a->No - b->No;
}

// 比較関数（Phy 昇順、同点なら No 昇順
int physort(const void *X, const void *Y) {
    const struct student *a = (const struct student *)X;
    const struct student *b = (const struct student *)Y;
    if (a->Phy != b->Phy) return a->Phy - b->Phy;
    return a->No - b->No;
}

// 学生の情報を整形して表示する関数
static void print_line(const char *label, const struct student S[], int n, int which) {
    printf("%s:", label);
    for (int i = 0; i < n; ++i) {
        int v = (which==0)? S[i].No : (which==1? S[i].Math : S[i].Phy);
        printf(" %2d", v);
    }
    printf("\n");
}

// ブロックごとにタイトルをつけてデータを表示
static void print_block(const char *title, const struct student S[], int n) {
    printf("\n%s\n", title);
    print_line("No  ", S, n, 0);
    print_line("Math", S, n, 1);
    print_line("Phy ", S, n, 2);
}

int main(void){
    int i;
    struct student S[N];

    srand(SEED); // 学籍番号下3桁など、固定シード

    for(i = 0; i < N; i++){
        S[i].No   = i + 1;
        S[i].Math = rand() % 101; // 0〜100
        S[i].Phy  = rand() % 101; // 0〜100
    }

    // ソート前のデータの表示
    print_block("Before sorting", S, N);

    // Math 点数による qsort の利用
    qsort((void*)S, N, sizeof(S[0]), mathsort);
    print_block("After sorting for Math", S, N);

    // Phy 点数による qsort の利用
    qsort((void*)S, N, sizeof(S[0]), physort);
    print_block("After sorting for Phy", S, N);

    return 0;
}
