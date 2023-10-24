#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Змінні для зберігання опцій
char *FILE_NAME = "result";  // Значення за промовчанням
int NUM_PROGRAMS = 0;

// Функція для запуску дочірньої програми
void run_child_program(int program_number) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_%d.txt", FILE_NAME, program_number);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Помилка відкриття файлу");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < program_number; i++) {
        fprintf(file, "%f\n", (double)rand() / RAND_MAX);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "f:n:")) != -1) {
        switch (opt) {
            case 'f':
                FILE_NAME = optarg;
                break;
            case 'n':
                NUM_PROGRAMS = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Використання: %s [-f FILE_NAME] [-n NUM_PROGRAMS]\n", argv[0]);
                exit(1);
        }
    }

    if (NUM_PROGRAMS <= 0) {
        fprintf(stderr, "Вказано некоректну кількість дочірніх програм\n");
        exit(1);
    }

    for (int i = 1; i <= NUM_PROGRAMS; i++) {
        pid_t child_pid = fork();
        if (child_pid < 0) {
            perror("Помилка fork");
            exit(1);
        } else if (child_pid == 0) {
            run_child_program(i);
            exit(0);
        } else {
            // Батьківський процес чекає завершення дочірньої програми
            wait(NULL);
        }
    }

    return 0;
}

