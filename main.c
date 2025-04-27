#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ARRAY_SIZE 1000000 
#define NUM_THREADS 4

void fill_array_random(int *arr) {
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = rand() % 100; // Заполняем случайными числами от 0 до 99
    }
}

// Последовательный вариант
long long sequential_sum(int *arr) {
    long long sum = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += arr[i];
    }
    return sum;
}

// Параллельный вариант
long long parallel_sum(int *arr) {
    long long sum = 0;
    #pragma omp parallel num_threads(NUM_THREADS) reduction(+:sum)
    {
        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    fill_array_random(array);

    // Последовательный вариант
    clock_t start_time = clock();
    long long sequential_result = sequential_sum(array);
    clock_t end_time = clock();
    double sequential_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Последовательная сумма: %lld\n", sequential_result);
    printf("Время последовательного выполнения: %f секунд\n", sequential_time);

    // Параллельный вариант
    start_time = clock();
    long long parallel_result = parallel_sum(array, ARRAY_SIZE);
    end_time = clock();
    double parallel_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Параллельная сумма: %lld\n", parallel_result);
    printf("Время параллельного выполнения: %f секунд\n", parallel_time);

    free(array);

    return 0;
}
