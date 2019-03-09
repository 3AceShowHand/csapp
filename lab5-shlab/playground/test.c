#include <stdio.h>
#include <stdlib.h>

int main() {

    const char* target = "%54";
    int jid = atoi(++target);
    printf("jid is %d\n", jid);
    
    return 0;
}
