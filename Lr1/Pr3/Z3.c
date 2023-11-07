#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_ITERATIONS 10

// Function for the first thread - outputting a string
void *outputString() {


    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3); // Sleep for a random number of seconds (0-2)
    }

    pthread_exit(NULL);
}

// Function for the second thread - generating random numbers
void *generateRandomNumbers(void *arg) {
    int targetNumber = *((int *)arg);

    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        int randomNum = rand() % 100; // Generate a random number in the range 0-99
        printf("Random Number Thread. Iteration: %d, Random Number: %d\n", i, randomNum);

        if (randomNum == targetNumber) {
            printf("Random Number Thread: Found target number. Exiting.\n");
            pthread_exit(NULL);
        }

        sleep(rand() % 3); // Sleep for a random number of seconds (0-2)
    }

    pthread_exit(NULL);
}

int main() {
    // Initialize the random number generator
    srand(time(NULL));

    pthread_t stringThread, numberThread;
    int targetNumber = 42; // The target number to look for

    // Create a thread for outputting the string
    if (pthread_create(&stringThread, NULL, outputString, "Hello, World!") != 0) {
        perror("pthread_create (String Thread)");
        exit(1);
    }

    // Create a thread for generating random numbers
    if (pthread_create(&numberThread, NULL, generateRandomNumbers, &targetNumber) != 0) {
        perror("pthread_create (Random Number Thread)");
        exit(1);
    }

    // Wait for both threads to finish
    if (pthread_join(stringThread, NULL) != 0) {
        perror("pthread_join (String Thread)");
        exit(1);
    }

    if (pthread_join(numberThread, NULL) != 0) {
        perror("pthread_join (Random Number Thread)");
        exit(1);
    }

    printf("Main Thread: All threads have finished.\n");

    return 0;
}
