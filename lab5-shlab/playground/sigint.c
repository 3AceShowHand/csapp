#include "helper.h"

void sigint_handler(int sig) {
    printf("Caught SIGNIT!\n");
    exit(0);
}

int main() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        unix_error("signal error");
    }
    pause();
    return 0;
}