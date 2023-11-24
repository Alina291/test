#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITERATIONS 10

// Функція, яку виконує новий потік
void *childThread(void *arg) {
    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3); // Засипаємо на випадкову кількість секунд (0-2)
    }
    pthread_exit(NULL);
}

int main() {
    // Ініціалізуємо генератор випадкових чисел
    srand(time(NULL));

    pthread_t tid; // Змінна для збереження ідентифікатора нового потоку

    // Створюємо новий потік
    if (pthread_create(&tid, NULL, childThread, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3); // Засипаємо на випадкову кількість секунд (0-2)
    }

    // Очікуємо завершення нового потоку
    if (pthread_join(tid, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }

    return 0;
}
