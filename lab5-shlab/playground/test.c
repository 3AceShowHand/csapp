#include <stdio.h>


int main() {

    const char* strings[] = {"hello", "world."};
    printf("size of strings: %d\n", sizeof(strings));    
    
    const char* a[] = {"a"};
    printf("%d\n", sizeof(a));
    
    return 0;
}
