#include "helper.h"

int main(int args, char** argv, char** envp) {
    printf("Command-line arguments:\n");
    for (int i = 0; i < args; i++) {
        printf("   argv[%2d]: %s\n", i, argv[i]);
    }

    printf("Environment variables:\n");
    for (int i = 0; envp[i] != NULL; i++) {
        printf("   envp[%2d]: %s\n", i, envp[i]);
    }

    return 0;
}