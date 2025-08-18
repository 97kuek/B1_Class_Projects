#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 比較関数
int char_sort(const void *a, const void *b) {
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;
    return (ca > cb) - (ca < cb);  /* 安全で分岐の少ない書き方 */
}

int main(void) {
    char s[1024];

    // 入力
    printf("Input a string:");
    if (!fgets(s, sizeof s, stdin)) return 0;

    // 末尾の改行を削除
    size_t n = strlen(s);                           // 文字列の長さを取得
    if (n && s[n-1] == '\n') s[--n] = '\0';         // 改行を削除 

    qsort((void *)s, n, sizeof(s[0]), char_sort);   // 文字列をソート

    // 出力
    puts(s);
    return 0;
}
