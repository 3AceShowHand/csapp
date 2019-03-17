#include <stdio.h>
#include <string.h>
#include "helper.h"

/* 
* convert hex to dotted-decimal representation
*/
int main(int argc, char* argv[]) {
    struct in_addr inaddr;
    uint32_t addr;
    char buf[100];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <hex number> \n", argv[0]);
        exit(0);
    }
    sscanf(argv[1], "%x", &addr);
    inaddr.s_addr = htonl(addr);

    if (!inet_ntop(AF_INET, &inaddr, buf, 100)) {
        unix_error("inet_ntop");
    }
    printf("%s\n", buf);

    return 0;
}