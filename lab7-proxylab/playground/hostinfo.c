#include "helper.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    struct addrinfo *p;
    struct addrinfo *listp;
    struct addrinfo hints;
    char buf[MAXLINE];
    int rc, flag;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(0);
    }

    flag = NI_NUMERICHOST;
    for (p = listp; p != NULL; p = p->ai_next) {
        getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flag);
        printf("%s\n", buf);
    }

    freeaddrinfo(listp);
    return 0;
}