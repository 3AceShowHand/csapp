/* 
 * myint.c - Another handy routine for testing your tiny shell
 * 
 * usage: myint <n>
 * Sleeps for <n> seconds and sends SIGINT to itself.
 *
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int i, secs;
    pid_t pid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        exit(0);
    }
    secs = atoi(argv[1]);

    for (i = 0; i < secs; i++)
        sleep(1);

    pid = getpid();

    if (kill(pid, SIGINT) < 0)
        fprintf(stderr, "kill (int) error");

    exit(0);
}
