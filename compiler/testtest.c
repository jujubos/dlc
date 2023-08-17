#include <stdlib.h>
#include <stdio.h>

void reverse(char *str) {
    if(str == NULL) return;
    char *end = str;
    while(*end) end ++;
    end --;
    while(str > end) {
        char t = *str;
        *str = *end;
        *end = t;
        str ++, end --;
    }
}

int main() {
    char buf[] = "123";
    printf("%s\n", buf);
    reverse(buf);
    printf("%s\n", buf);

    return 0;
}