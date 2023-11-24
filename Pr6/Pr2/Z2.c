#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

// Structure to hold thread parameters
struct ThreadArgs {
    char *name;
    char *str;
    int num;
};

// Thread function
void *threadFunction(void *arg) {
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)arg;
    char *name = threadArgs->name;
    char *str = threadArgs->str;
    int num = threadArgs->num;

    for (int i = 1; i <= num; i++) {
        printf("Thread %s. Str %s %d\n", name, str, i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Define parameters for each thread
    struct ThreadArgs threadArgs[NUM_THREADS] = {
            {"A", "Hello", 3},
            {"B", "Hi", 4},
            {"C", "Welcome", 2},
            {"D", "Goodbye", 5}
    };

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for the threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    return 0;
}
