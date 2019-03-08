#include "helper.h"

// int main() {
//     pid_t pid;
//     int x = 1;

//     pid = Fork();
//     if (pid == 0) {
//         printf("child: x = %d\n", ++x);
//         exit(0);
//     }

//     printf("parent: x = %d\n", --x);
//     exit(0);

//     return 0;
// }

int main() {
    Fork();
    Fork();
    printf("Hello world.");

    return 0;
}