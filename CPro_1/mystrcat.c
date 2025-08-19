#include <stdio.h>
#include <string.h>

// 文字列を連結する関数mystrcat
void mystrcat(char *a, char *b){
    char c[200];
    size_t i = 0, j = 0;

    // 「文字列aはヌル文字になる」かつ「cのサイズを超えない」までaをcにコピー
    while (a[i] != '\0' && i < sizeof(c) - 1) {
        c[i] = a[i];
        i++;
    }
    // 「文字列bはヌル文字になる」かつ「cのサイズを超えない」までbをcにコピー
    while (b[j] != '\0' && i < sizeof(c) - 1) {
        c[i] = b[j];    // c[i-1]まではaの内容が入っている
        i++; j++;
    }
    c[i] = '\0';

    printf("string1+string2: %s\n", c);
}

int main(void){
    char string1[100], string2[100];

    printf("Input string1 and string2\n");
    printf("string1:");
    scanf("%99s", string1);
    printf("string2:");
    scanf("%99s", string2);

    mystrcat(string1, string2);
    return 0;
}
