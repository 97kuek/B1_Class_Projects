#include <stdio.h>

// 小文字の文字列を大文字に変換して表示する関数mystrconv
void mystrconv(char *string){
    int n = 0;
    printf("Uppercase string:");
    while (string[n] != '\0') {      // 末尾のヌル文字まで走査
        char c = string[n];          // 文字を取得
        if (c >= 'a' && c <= 'z') {  // 小文字の範囲かチェック
            /*
            'a' から 'z' の範囲の文字は、ASCIIコードで 'a' が 97、'z' が 122
            です。大文字の 'A' は 65、'Z' は 90 なので、ASCIIコードの差は 32 です。
            したがって、小文字を大文字に変換するには、ASCIIコードから 32 を引きます。
            */
            c = c - ('a' - 'A'); 
        }
        printf("%c", c);
        n++;
    }
    printf("\n");
}

int main(void){
    char string[100];

    printf("Input a lowercase string:");
    scanf("%99s", string);

    mystrconv(string);
    return 0;
}
