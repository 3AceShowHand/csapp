#include "helper.h"

void handler1(int sig) {
    int olderrno = errno;

    while (waitpid(-1, NULL, 0) > 0) {
        sio_puts("Handler reaped child\n");
    }
    if (errno != ECHILD) {
        sio_error("waitpid error");
    }
    sleep(1);
    errno = olderrno;
}

int main() {
    int i, n;
    char buf[MAXBUF];

    if (signal(SIGCHLD, handler1) == SIG_ERR) {
        unix_error("signal error");
    }

    for (i = 0; i < 3; i++) {
        if (Fork() == 0) {
            printf("Hello from child %d\n", (int)getpid());
            exit(0);
        }
    }

    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0) {
        unix_error("read");
    }

    printf("Parent processing input\n");
    while (1) {
        ;
    }
    exit(0);
}