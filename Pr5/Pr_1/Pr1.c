#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Використання: %s 'команди'\n", argv[0]);
        return 1;
    }

    char *commands = argv[1];  // Отримуємо рядок з командами з командного рядка

    // Розділяємо команди за допомогою strtok() та виконуємо їх за допомогою системної функції
    char *token = strtok(commands, ";");
    while (token != NULL) {
        int exit_code = system(token);

        // Перевіряємо код завершення
        if (WIFEXITED(exit_code)) {
            printf("Команда '%s' виконана з кодом завершення %d\n", token, WEXITSTATUS(exit_code));
        } else {
            printf("Помилка виконання команди '%s'\n", token);
        }

        token = strtok(NULL, ";");
    }

    return 0;
}
