#include "helper.h"

unsigned int snooze(unsigned int secs) {
    unsigned int rc = sleep(secs);
    printf("Slept for % d of %d secs. \n", secs - rc, secs);

    return rc;
}

void sigint_handler(int sig) {
    return;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        return 0;
    }

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        unix_error("signal error");
    }
    snooze(atoi(argv[1]));
    printf("after snooze");

    return 0;
}