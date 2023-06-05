#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define ARRAY_SIZE 10000000
#define NUM_THREADS 4

bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int countPrimes(int array[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (isPrime(array[i])) {
            count++;
        }
    }
    return count;
}

int* selectSubarray(int array[], int start, int end) {
    int size = end - start + 1;
    int* subarray = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        subarray[i] = array[start + i];
    }

    return subarray;
}

int array[ARRAY_SIZE];
long long int sum = 0;
pthread_mutex_t mutex;

void* calculate_sum(void* arg) {
    int thread_id = *((int*)arg);
    long long int partial_sum = 0;
    
    int start = thread_id * (ARRAY_SIZE / NUM_THREADS);
    int end = start + (ARRAY_SIZE / NUM_THREADS);

    int* subarray = selectSubarray(array, start, end);

    int size = end - start;
    int primeCount = countPrimes(subarray, size);
    
    pthread_mutex_lock(&mutex);
    printf("%d\n", primeCount);
    sum += primeCount;
    pthread_mutex_unlock(&mutex);
    free(subarray);
    
    return NULL;
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100000;
    }
    
    
    pthread_mutex_init(&mutex, NULL);
    
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, calculate_sum, &thread_ids[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    
    printf("Number of prime numbers: %lld\n", sum);
    
    return 0;
}

