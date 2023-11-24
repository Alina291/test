#include <stdio.h>
#include <stdlib.h>

// Структура для представлення точки
struct Point {
    int id;     // Ідентифікатор точки
    int mass;   // Маса точки
    struct Point* next; // Вказівник на наступну точку
};

// Функція для створення нової точки
struct Point* createPoint(int id, int mass) {
    struct Point* point = (struct Point*)malloc(sizeof(struct Point));
    if (point == NULL) {
        fprintf(stderr, "Memory allocation error for point.\n");
        exit(1);
    }
    point->id = id;
    point->mass = mass;
    point->next = NULL;
    return point;
}

// Функція для додавання точки в кінець списку
void addPoint(struct Point** head, struct Point* newPoint) {
    if (*head == NULL) {
        *head = newPoint;
    } else {
        struct Point* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPoint;
    }
}

// Функція для видалення точки за ідентифікатором
void removePoint(struct Point** head, int id) {
    if (*head == NULL) {
        return; // Список порожній, немає точок для видалення
    }

    if ((*head)->id == id) {
        struct Point* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    struct Point* current = *head;
    while (current->next != NULL && current->next->id != id) {
        current = current->next;
    }

    if (current->next == NULL) {
        return; // Точку з заданим id не знайдено
    }

    struct Point* temp = current->next;
    current->next = temp->next;
    free(temp);
}

// Функція для знаходження залишеної точки після передачі маси
int findRemainingPoint(struct Point* head) {
    while (head->next != NULL) {
        struct Point* minMassPoint = head;
        struct Point* current = head->next;
        while (current != NULL) {
            if (current->mass < minMassPoint->mass) {
                minMassPoint = current;
            }
            current = current->next;
        }
        head->mass += minMassPoint->mass;
        removePoint(&head, minMassPoint->id);
    }
    return head->id;
}

// Функція для звільнення пам'яті, включаючи всі точки
void freePoints(struct Point* head) {
    while (head != NULL) {
        struct Point* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n;
    printf("Введіть кількість матеріальних точок: ");
    scanf("%d", &n);

    struct Point* head = NULL;

    // Заповнюємо список матеріальними точками
    for (int i = 1; i <= n; i++) {
        int mass;
        printf("Введіть масу точки %d: ", i);
        scanf("%d", &mass);
        struct Point* point = createPoint(i, mass);
        addPoint(&head, point);
    }

    // Знаходимо залишену точку після передачі маси
    int remainingPoint = findRemainingPoint(head);

    printf("Залишена точка з ідентифікатором: %d\n", remainingPoint);

    // Звільнюємо пам'ять
    freePoints(head);

    return 0;
}
