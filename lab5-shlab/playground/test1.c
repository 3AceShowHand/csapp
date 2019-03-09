#include <stdio.h>
#include <wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


int val = 10;

void handler(int sig) {
	val += 5;
}

int main() {
	signal(SIGCHLD, handler);
	pid_t pid;

	if ((pid = fork()) == 0) {
        	val -= 3;
		exit(0);
        }
	waitpid(pid, NULL, 0);
	printf("val = %d\n", val);
	exit(0);
}
