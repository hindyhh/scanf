# include <stdio.h>
# include <assert.h>
# include <string.h>
# include "my_scanf.h"

void push_int(int n) {
    char buffer[12];
    int len = sprintf(buffer, "%d", n);

    ungetc(' ', stdin);
    for (int i = len - 1; i >= 0; i--) {
        ungetc(buffer[i], stdin);
    }
}

void test_digit(void) {
    for (int i = -100; i <= 100; i++) {
        int x = 0;

        push_int(i);
        int r = my_scanf ("%d", &x);

        assert(r == 1);
        assert(x == i);
    }
    printf("All digit tests passed!\n");
}

int main (void) {
    printf("Running tests...\n");
    test_digit();
    return 0;
}