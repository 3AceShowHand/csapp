#include <stdio.h>

static inline int foo() {
    return 2;
}

int main() {
    int ret;
    ret = foo();

    printf("Output is %d\n", ret);

    return 0;
}
