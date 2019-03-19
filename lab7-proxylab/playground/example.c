#include <stdio.h>
#include <string.h>

int main() {
    // char str[] = "http://zhihu.com/";
    char str[] = "http://www.cmu.edu:8080/hub/index.html";
    char* token;
    char* rest = str;
    const char* delim = "/";
    token = strtok_r(rest, delim, &rest);
    token = strtok_r(rest, delim, &rest);
    printf("%s\n", rest);
    if (strstr(token, ":")) {
        token = strtok_r(token, ":", &rest);
        printf("%s\n", token);
        printf("%s\n", rest);
    }
    return 0;
}
