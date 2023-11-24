#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Hostname: %s\n", hostname);
    } else {
        perror("Error getting hostname");
    }

    struct utsname sys_info;
    if (uname(&sys_info) == 0) {
        printf("System Information:\n");
        printf("System Name: %s\n", sys_info.sysname);
        printf("Node Name: %s\n", sys_info.nodename);
        printf("Release: %s\n", sys_info.release);
        printf("Version: %s\n", sys_info.version);
        printf("Machine: %s\n", sys_info.machine);
    } else {
        perror("Error getting system information");
    }

    return 0;
}