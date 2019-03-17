#include <stdio.h>
#include <string.h>
#include "helper.h"

/*
* convert dotted-decimal representation of Ip address
* to corresponding hex representation.
*/

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <dotted-decimal representation of IP address> \n", argv[0]);
        exit(0);
    }
    struct in_addr inaddr;
    int rc = inet_pton(AF_INET, argv[1], &inaddr.s_addr);
    if (rc == -1) {
        unix_error("inet_pton error\n");
    } else if (rc == 0) {
        unix_error("invalid argv[1]\n");
    } else {
        printf("0x%x\n", ntohl(inaddr.s_addr));
    }
    return 0;
}