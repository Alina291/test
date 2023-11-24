#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

struct MyArrayList {
    int* array;
    int size;
    int capacity;
};

struct MyArrayList* createArrayList() {
    struct MyArrayList* list = (struct MyArrayList*)malloc(sizeof(struct MyArrayList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation error for the list.\n");
        exit(1);
    }

    list->array = (int*)malloc(sizeof(int) * INITIAL_CAPACITY);
    if (list->array == NULL) {
        fprintf(stderr, "Memory allocation error for the array.\n");
        exit(1);
    }

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return list;
}

void add(struct MyArrayList* list, int item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, sizeof(int) * list->capacity);
        if (list->array == NULL) {
            fprintf(stderr, "Memory reallocation error.\n");
            exit(1);
        }
    }
    list->array[list->size++] = item;
}

void insert(struct MyArrayList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Invalid index for insertion.\n");
        return;
    }

    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, sizeof(int) * list->capacity);
        if (list->array == NULL) {
            fprintf(stderr, "Memory reallocation error.\n");
            exit(1);
        }
    }

    for (int i = list->size; i > index; i--) {
        list->array[i] = list->array[i - 1];
    }

    list->array[index] = item;
    list->size++;
}

int size(struct MyArrayList* list) {
    return list->size;
}

void removeElement(struct MyArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Invalid index for removal.\n");
        return;
    }

    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }

    list->size--;

    // Reduce the capacity if the size is significantly smaller than the capacity
    if (list->size < list->capacity / 2) {
        list->capacity /= 2;
        list->array = (int*)realloc(list->array, sizeof(int) * list->capacity);
        if (list->array == NULL) {
            fprintf(stderr, "Memory reallocation error.\n");
            exit(1);
        }
    }
}

void set(struct MyArrayList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Invalid index for setting value.\n");
        return;
    }
    list->array[index] = item;
}

int get(struct MyArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Invalid index for getting value.\n");
        return -1; // Return a default value
    }
    return list->array[index];
}

void destroyArrayList(struct MyArrayList* list) {
    free(list->array);
    free(list);
}

int main() {
    struct MyArrayList* myList = createArrayList();

    add(myList, 1);
    add(myList, 2);
    insert(myList, 1, 1.5);

    printf("Size of the list: %d\n", size(myList));
    printf("Element at index 1: %d\n", get(myList, 1));

    removeElement(myList, 0);
    set(myList, 1, 3);

    destroyArrayList(myList);

    return 0;
}
