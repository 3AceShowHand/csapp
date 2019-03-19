#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "http://zhihu.com/";
    // char str[] = "http://www.cmu.edu/hub/index.html";
    char* token;
    char* rest = str;
    const char* delim = "/";
    token = strtok_r(rest, delim, &rest);
    token = strtok_r(rest, delim, &rest);
    printf("%s\n", token);
    printf("%s\n", rest);
    printf("size of rest: %d\n", strlen(rest));

    return 0;
}
