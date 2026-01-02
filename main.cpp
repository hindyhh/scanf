#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

// pass through all the spaces returning the next non-space character
static int skip_space(int c) {
    while (isspace(c)) {
        c = getchar();
    }
    return c;
}

// returns if chars_read is within the width amount
static int check_width(int width, int chars_read) {
    return width == 0 || chars_read < width;
}

int my_scanf(const char *format, ...) {
    // initializing the list and the number of times variables were assigned
    va_list args;
    int count = 0;

    // starting the pointer
    va_start(args, format);

    // starting with the first character
    int c = getchar();

    // skip spaces in the format
    while (*format) {
        if (isspace(*format)) {
            format++;
            continue;
        }

        if (*format == '%') {
            format++;

            // check if there is a width limit to how long the input can be
            int width = 0;
            while (isdigit(*format)) {
                width = width * 10 + (*format - '0');
                format++;
            }

            switch (*format) {

                case 'd': {
                    // get the int pointer from the list
                    int *out = va_arg(args, int*);
                    int value = 0;
                    int sign = 1;
                    int chars_read = 0;

                    c = skip_space(c);

                    // update sign if the number is negative
                    if (c == '-') {
                        sign = -1;
                        c = getchar();
                    } else if (c == '+') {
                        c = getchar();
                    }

                    while (isdigit(c) && check_width(width, chars_read)) {
                        // add the next digit after the previous ones
                        value = value * 10 + c - '0';
                        chars_read++;
                        c = getchar();
                    }
                    // store the answer
                    *out = value * sign;
                    count++;
                    break;
                }

                case 's': {
                    // get the char pointer from the list
                    char *out = va_arg(args, char *);
                    int chars_read = 0;

                    c = skip_space(c);

                    // while we are still in the string
                    while (c != EOF && !isspace(c) && check_width(width, chars_read)) {
                        // store the next character
                        *out++ = (char)c;
                        chars_read++;
                        c = getchar();
                    }
                    *out = '\0';
                    count++;
                    break;
                }

                case 'c': {
                    // get the char pointer from the list and store the answer
                    char *out = va_arg(args, char *);
                    *out = (char)c;
                    count++;
                    c = getchar();
                    break;
                }

                case 'f': {
                    // get the float pointer from the list
                    float *out = va_arg(args, float *);
                    double result = 0.0;
                    double factor = 1.0;
                    int sign = 1;
                    int chars_read = 0;
                    int decimal_found = 0;

                    c = skip_space(c);

                    // update sign if it is negative
                    if (c == '-') {
                        sign = -1;
                        c = getchar();
                    } else if (c == '+') {
                        c = getchar();
                    }

                    while (isdigit(c) || c == '.' && check_width(width, chars_read)) {
                        if (c == '.') {
                            // update the decimal flag
                            decimal_found = 1;
                        }else {
                            // add the next digit at the end of the previous ones
                            result = result * 10.0 + (c - '0');
                            // for each decimal place update factor
                            if (decimal_found) {
                                factor *= 10.0;
                            }
                        }
                        chars_read++;
                        c = getchar();
                    }
                    // store the answer with the correct decimal place and sign
                    *out = (float)(sign * result/factor);
                    count++;
                    break;
                }

                case 'x': {
                    // get the unsigned int pointer
                    unsigned int *out = va_arg(args, unsigned int *);
                    unsigned int value = 0;
                    int chars_read = 0;

                    c = skip_space(c);

                    // account for hexadecimal notation
                    if (c == '0') {
                        c = getchar();
                        if (c == 'x' || c == 'X') {
                            c = getchar();
                        }else {
                            value = 0;
                            chars_read++;
                        }
                    }

                    while (isxdigit(c) && check_width(width, chars_read)) {
                        // shift the previous value to the left
                        value *= 16;
                        // add the next digit or letter at the end
                        if (isdigit(c)) {
                            value += c - '0';
                        } else {
                            value += tolower(c) - 'a' + 10;
                        }
                        chars_read++;
                        c = getchar();
                    }
                    // store the answer
                    *out = value;
                    count++;
                    break;
                }
            }
        }else {
            // if the input and format match move on
            if (c == *format) {
                c = getchar();
            }
        }
        format++;
    }
    // end the pointer
    va_end(args);
    return count;
}

int main() {
    int i;
    unsigned int x;
    float f;
    char s[100];
    char c;
    int result;

    printf("-----Test myscanf-------\n");

    printf("Enter an integer: ");
    result = my_scanf("%d", &i);
    printf("Result count: %d | Values: i=%d\n\n", result, i);

    printf("Enter a string and char: ");
    result = my_scanf("%s %c", s, &c);
    printf("Result count: %d | Values: s=%s, c=%c\n\n", result, s, c);

    printf("Enter a hex number: ");
    result = my_scanf("%x", &x);
    printf("Result count: %d | Values: x=%x\n\n", result, x);

    printf("Enter a float: ");
    result = my_scanf("%f", &f);
    printf("Result count: %d | Values: f=%f\n\n", result, f);

    return 0;
}