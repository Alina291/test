#include <stdio.h>
#include <math.h>

int main() {
    int n;
    printf("Введіть розмір масиву: ");
    scanf("%d", &n);

    // Перевірка на неправильний введений розмір
    if (n <= 0) {
        printf("Розмір масиву повинен бути більше 0.\n");
        return 1; // Помилка
    }

    double arr[n];
    printf("Введіть %d дійсних чисел через пробіл: ", n);

    // Заповнення масиву
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }

    // Обчислення середнього значення
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    double average = sum / n;

    // Лічильник елементів більших за середнє значення
    int count = 0;

    // Сума модулів елементів після першого від'ємного елемента
    double sum_after_negative = 0;

    int found_negative = 0; // Прапорець, який показує, чи знайдено перший від'ємний елемент

    for (int i = 0; i < n; i++) {
        if (arr[i] > average) {
            count++;
        }

        if (found_negative) {
            sum_after_negative += fabs(arr[i]); // Використовуємо функцію fabs для обчислення модулю числа
        }

        if (arr[i] < 0) {
            found_negative = 1;
        }
    }

    printf("Кількість елементів, більших за середнє значення: %d\n", count);
    printf("Сума модулів елементів після першого від'ємного елемента: %.2lf\n", sum_after_negative);

    return 0;
}
