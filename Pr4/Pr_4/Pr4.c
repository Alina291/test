#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    uid_t uid = getuid();

    struct passwd *pw = getpwuid(uid);
    if (pw == NULL) {
        printf("Error getting user information.\n");
        return 1;
    }

    printf("User name: %s\n", pw->pw_name);
    printf("Full name: %s\n", pw->pw_gecos);
    printf("Home directory: %s\n", pw->pw_dir);
    printf("Path to the user's shell: %s\n", pw->pw_shell);

    pw = getpwnam("root");
    if (pw == NULL) {
        printf("Error getting user information.\n");
        return 1;
    }

    printf("User name: %s\n", pw->pw_name);
    printf("Full name: %s\n", pw->pw_gecos);
    printf("Home directory: %s\n", pw->pw_dir);
    printf("Path to the root user's shell: %s\n", pw->pw_shell);

    return 0;
}