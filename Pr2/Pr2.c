#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int playOneRound(int bet);
int generateRandomSymbol();

int main() {
    // Ініціалізуємо генератор випадкових чисел від часу
    srand(time(NULL));

    int balance = 1000;

    while (balance > 0) {
        printf("Enter from 1 to %d\n", balance);

        int bet; // Ставка гравця
        printf("Make a bet (or 0 to exit):");
        scanf("%d", &bet);

        if (bet == 0) {
            break;
        }

        if (bet > balance) {
            printf("Your bet is bigger than balance, try again.\n");
            continue;
        }

        int result = playOneRound(bet);

        if (result > 0) {
            balance += result;
            printf("You won %d!\n", result);
        } else {
            balance -= bet;
            printf("You lost your bet.\n");
        }
    }

    printf("Game over!\n");

    return 0;
}

// Функція для генерації випадкового числа від 1 до 9
int generateRandomSymbol() {
    return rand() % 9+1;
}

int playOneRound(int bet) {
    int digits[3]; // Масив для збереження цифр

    printf("Random numbers: ");
// Генеруємо випадкові цифри
    for (int i = 0; i < 3; i++) {
        digits[i] = generateRandomSymbol();
        printf("%d ", digits[i]);
    }

    printf("\n");
    // Перевіряємо умови перемоги

    if (digits[0] == digits[1] && digits[1] == digits[2]) {
        if (digits[0] == 7) {
            return bet * 3;
        }
        return bet * 2;
    }

    for (int i = 0; i < 3; i++) {
        if (digits[i] == 7) {
            return bet;
        }
    }


    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (digits[i] == digits[j]) {
                return bet;
            }
        }
    }

    return 0;
}