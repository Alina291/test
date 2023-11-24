#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage of program:\n\n%s <environment_variable_name> <value>\n", argv[0]);
        return 1;
    }

    char *name = argv[1];
    char *value = argv[2];

    int result = setenv(name, value, 1);
    if (result == -1) {
        printf("Error setting the value of the environment variable.\n");
        return 1;
    }

    char *get_value = getenv(name);
    if (get_value == NULL) {
        printf("Environment variable with name '%s' does not exist.\n", name);
        return 1;
    }

    printf("Environment variable '%s': %s\n", name, get_value);
    return 0;
}