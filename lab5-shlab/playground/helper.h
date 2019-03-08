#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 8192
#define MAXBUF 8192

void unix_error(char* msgs) {
    fprintf(stderr, "%s, %s\n", msgs, strerror(errno));
    exit(0);
}

void app_error(char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(0);
}

pid_t Fork() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        unix_error("Fork error");
    }
    return pid;
}

handler_t* Signal(int signum, handler_t* handler) {
    struct sigaction action, old_action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    if (sigaction(signum, &action, &old_action) < 0) {
        unix_error("Signal error");
    }
    return (old_action.sa_handler);
}

char* Fgets(char* ptr, int n, FILE* stream) {
    char* rptr;
    if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
        app_error("Fgets error");
    }
    return rptr;
}

static void sio_reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void sio_ltoa(long v, char s[], int b) {
    int c, i = 0;
    do {
        s[i++] = ((c = (v % b)) < 10) ? c + '0' : c - 10 + 'a';
    } while ((v /= b) > 0);
    s[i] = '\0';
    sio_reverse(s);
}

static size_t sio_strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
}

ssize_t sio_puts(char s[]) {
    return write(STDOUT_FILENO, s, sio_strlen(s));
}

ssize_t sio_putl(long v) {
    char s[128];
    sio_ltoa(v, s, 10);
    return sio_puts(s);
}

void sio_error(char s[]) {
    sio_puts(s);
    _exit(1);
}