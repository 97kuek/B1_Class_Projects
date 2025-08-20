#include <stdio.h>

int main(void)
{
    int math, eng, sci;
    int total;
    double avg;
    char grade[4];

    printf("Input your scores:\n");

    printf("Math: ");
    scanf("%d", &math);

    printf("English: ");
    scanf("%d", &eng);

    printf("Science: ");
    scanf("%d", &sci);

    total = math + eng + sci;
    avg = total / 3.0;

    if (total >= 270) {
        sprintf(grade, "A++");
    } else if (total >= 240) {
        sprintf(grade, "A");
    } else if (total >= 210) {
        sprintf(grade, "B");
    } else if (total >= 180) {
        sprintf(grade, "C");
    } else {
        sprintf(grade, "F");
    }

    printf("Your grade is %s (Average is %.1f).\n", grade, avg);

    return 0;
}
