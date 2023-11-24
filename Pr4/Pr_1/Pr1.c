#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    extern char **environ;
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
    if (argc != 2) {
        printf("Program usage:\n\n%s <name_variable_environment>\n", argv[0]);
        return 1;
    }

    char *value = getenv(argv[1]);
    if (value == NULL) {
        printf("Variable '%s' not exist in the environment.\n", argv[1]);
        return 1;
    }

    printf("Env variable %s=%s\n", argv[1], value);
    return 0;
}