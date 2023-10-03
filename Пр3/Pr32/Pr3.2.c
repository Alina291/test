#include <stdio.h>
#include <stdlib.h>

// Вузол зв'язаного списку
struct Node {
    int data;
    struct Node* next;
};

// Зв'язаний список
struct LinkedList {
    struct Node* head;
    int size;
};

// Функція для створення пустого зв'язаного списку
struct LinkedList* createLinkedList() {
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation error for the list.\n");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// Додавання елемента в кінець списку
void add(struct LinkedList* list, int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error for the new node.\n");
        exit(1);
    }
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
}

// Вставка елемента в середину списку за індексом
void insert(struct LinkedList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Invalid index for insertion.\n");
        exit(1);
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error for the new node.\n");
        exit(1);
    }
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

// Кількість елементів у списку
int size(struct LinkedList* list) {
    return list->size;
}

// Видалення елемента за індексом
void removeElement(struct LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Invalid index for removal.\n");
        exit(1);
    }

    struct Node* temp;

    if (index == 0) {
        temp = list->head;
        list->head = list->head->next;
    } else {
        struct Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }

    free(temp);
    list->size--;
}

// Заміна існуючого елемента за індексом
void set(struct LinkedList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Invalid index for setting value.\n");
        exit(1);
    }

    struct Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->data = item;
}

// Отримання значення заданого елемента за індексом
int get(struct LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Invalid index for getting value.\n");
        exit(1);
    }

    struct Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

// Виведення зв'язаного списку на екран
void printLinkedList(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Звільнення пам'яті, включаючи всі вузли списку
void destroyLinkedList(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    struct LinkedList* myList = createLinkedList();

    add(myList, 1);
    add(myList, 2);
    insert(myList, 1, 1.5);

    printf("Size of the list: %d\n", size(myList));
    printf("Element at index 1: %d\n", get(myList, 1));

    removeElement(myList, 0);
    set(myList, 1, 3);

    printLinkedList(myList);

    destroyLinkedList(myList);

    return 0;
}
