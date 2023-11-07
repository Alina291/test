#include <stdio.h>
#include <pthread.h>

#define MAX_N 20

// Функція для обчислення чисел Каталана за формулою
void calculate_catalan(int n, unsigned long long catalan[]) {
    catalan[0] = 1;

    for (int i = 1; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }
}

// Функція для перевірки, чи число є простим
int is_prime(int num) {
    if (num <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Функція для обчислення перших n простих чисел
void calculate_primes(int n, int primes[]) {
    int count = 0;
    int num = 2;

    while (count < n) {
        if (is_prime(num)) {
            primes[count] = num;
            count++;
        }
        num++;
    }
}

void *catalan_thread_function(void *arg) {
    int n = *((int *)arg);
    unsigned long long catalan[MAX_N];
    calculate_catalan(n, catalan);
    for (int i = 0; i <= n; i++) {
        printf("Catalan[%d] = %llu\n", i, catalan[i]);
    }
    pthread_exit(NULL);
}

void *primes_thread_function(void *arg) {
    int n = *((int *)arg);
    int primes[MAX_N];
    calculate_primes(n, primes);
    for (int i = 0; i < n; i++) {
        printf("Prime[%d] = %d\n", i, primes[i]);
    }
    pthread_exit(NULL);
}

int main() {
    int n_catalan = 10;  // Задана кількість чисел Каталана
    int n_primes = 10;   // Задана кількість простих чисел

    pthread_t catalan_thread, primes_thread;

    // Створення потоків для обчислення чисел Каталана та простих чисел
    pthread_create(&catalan_thread, NULL, catalan_thread_function, &n_catalan);
    pthread_create(&primes_thread, NULL, primes_thread_function, &n_primes);

    // Очікування завершення потоків
    pthread_join(catalan_thread, NULL);
    pthread_join(primes_thread, NULL);

    return 0;
}