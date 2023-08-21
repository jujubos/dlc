#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void emit(int t, ...) {
    va_list args;
    va_start(args, t);

}

int main() {
    char buf[] = "123";
    printf("%s\n", buf);
    reverse(buf);
    printf("%s\n", buf);

    return 0;
}