#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void process_handler(int signum) {
    static int counter = 1;
    printf("Обробник %d: Затримка 1 секунда\n", counter);
    sleep(1);
    counter++;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Використання: %s <кількість_обробників>\n", argv[0]);
        return 1;
    }

    int num_handlers = atoi(argv[1]);
    if (num_handlers <= 0) {
        printf("Невірно вказана кількість обробників.\n");
        return 1;
    }

    // Реєструємо обробники завершення процесу
    for (int i = 0; i < num_handlers; i++) {
        if (signal(SIGINT, process_handler) == SIG_ERR) {
            perror("Помилка під час реєстрації обробника");
            return 1;
        }
    }

    printf("Очікування завершення процесів...\n");

    // Безкінечний цикл для очікування обробки сигналів
    while (1) {
        pause();
    }

    return 0;
}
