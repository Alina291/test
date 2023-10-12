#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void show_environment() {
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

void get_variable_value(const char *variable) {
    char *value = getenv(variable);
    if (value) {
        printf("%s=%s\n", variable, value);
    } else {
        printf("Variable '%s' not found in the environment\n", variable);
    }
}

void set_variable_value(const char *variable, const char *value) {
    if (setenv(variable, value, 1) == 0) {
        printf("%s=%s\n", variable, value);
    } else {
        printf("Failed to set variable '%s'\n", variable);
    }
}

void delete_variable(const char *variable) {
    if (unsetenv(variable) == 0) {
        printf("Variable '%s' has been deleted\n", variable);
    } else {
        printf("Failed to delete variable '%s'\n", variable);
    }
}

void clear_environment() {
    while (*environ) {
        unsetenv(*environ);
        environ++;
    }
    printf("Environment cleared\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        show_environment();
    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: environ [OPTIONS]\n");
        printf("Options:\n");
        printf("  -h, --help            Show help message\n");
        printf("  -i, --info <variable> Show the value of a variable in the environment\n");
        printf("  -s, --set <variable=value> Set the value of a variable in the environment\n");
        printf("  -d, --del <variable>  Delete a variable from the environment\n");
        printf("  -c, --clear           Clear the environment\n");
    } else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0) {
        if (argc == 3) {
            get_variable_value(argv[2]);
        } else {
            printf("Please specify a variable to get its value\n");
        }
    } else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--set") == 0) {
        if (argc == 3) {
            set_variable_value(argv[2], "");
        } else if (argc == 4) {
            char *variable = strtok(argv[2], "=");
            char *value = strtok(NULL, "=");
            set_variable_value(variable, value);
        } else {
            printf("Please specify a variable and its value to set\n");
        }
    } else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--del") == 0) {
        if (argc == 3) {
            delete_variable(argv[2]);
        } else {
            printf("Please specify a variable to delete\n");
        }
    } else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--clear") == 0) {
        clear_environment();
    } else {
        printf("Invalid option. Use -h or --help to see the available options.\n");
    }

    return 0;
}