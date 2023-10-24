#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define MAX_BUFFER_SIZE 127

// Функція для виведення довідкової інформації
void print_help() {
    printf("Спрощений командний процесор (shell)\n");
    printf("Доступні опції:\n");
    printf("  -h, --help    Вивести довідкову інформацію\n");
    printf("  -b, --buffer  Задати розмір буфера (за замовчуванням %d)\n", MAX_BUFFER_SIZE);
}

int main(int argc, char *argv[]) {
    char *user = getpwuid(getuid())->pw_name;  // Отримуємо ім'я поточного користувача
    char prompt[100];
    int buffer_size = MAX_BUFFER_SIZE;

    // Обробка опцій командного рядка
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if ((strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) && i + 1 < argc) {
            buffer_size = atoi(argv[i + 1]);
        }
    }

    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        perror("Помилка виділення пам'яті для буфера");
        return 1;
    }

    printf("Ласкаво просимо, %s, до спрощеного командного процесора!\n", user);

    while (1) {
        snprintf(prompt, sizeof(prompt), "[%s]$", user); // Формування prompt
        printf("%s ", prompt);
        fflush(stdout);

        if (fgets(buffer, buffer_size, stdin) == NULL) {
            perror("Помилка читання команди");
            continue;
        }

        // Видалення символу нового рядка з команди
        size_t cmd_len = strlen(buffer);
        if (cmd_len > 0 && buffer[cmd_len - 1] == '\n') {
            buffer[cmd_len - 1] = '\0';
        }

        if (strcmp(buffer, "stop") == 0) {
            printf("Wait 3 seconds...\n");
            sleep(3);
            system("clear");
            break;
        }

        int exit_code = system(buffer);
        if (exit_code != 0) {
            printf("Помилка виконання команди. Код завершення: %d\n", exit_code);
        }
    }

    free(buffer);
    return 0;
}
