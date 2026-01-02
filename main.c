#include <stdio.h>
#include "my_scanf.h"

int main() {
    int i;
    unsigned int x;
    float f;
    char s[100];
    char c;
    int result;
    char y;
    int r;

    printf("-----Test myscanf-------\n");

    printf("integer: ");
    result = my_scanf("%d", &i);
    printf("count: %d\nvalues: i=%d\n\n", result, i);

    printf("string and char: ");
    result = my_scanf("%s %c", s, &c);
    printf("count: %d\nvalues: s=%s, c=%c\n\n", result, s, c);

    printf("hex number: ");
    result = my_scanf("%x", &x);
    printf("count: %d\nvalues: x=%x\n\n", result, x);

    printf("float: ");
    result = my_scanf("%f", &f);
    printf("count: %d\nvalues: f=%f\n\n", result, f);

    printf("ascii: ");
    result = my_scanf("%y", &y);
    printf("count: %d\nvalues: y=%c\n\n", result, y);

    printf("Roman Numerals: ");
    result = my_scanf("%r", &r);
    printf("count: %d\nvalue: %d\n\n", result, r);


    return 0;
}