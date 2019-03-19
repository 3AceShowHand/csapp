#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Host: zhihu.com";
    char* token;
    char* rest = str;
    const char* delim = ": ";
    while ((token = strtok_r(rest, delim, &rest))) {
        printf("%s\n", token);
    }

    return 0;
}
