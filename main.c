#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define ARRAY_SIZE 2000000
#define NUM_RUNS 1000

// Функция для заполнения массива случайными числами
void fill_array(double *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = (double)rand() / RAND_MAX;
    }
}

// Последовательное вычисление суммы
double sequential_sum(const double *array) {
    double sum = 0.0;
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
    return sum;
}

// Параллельное вычисление суммы с OpenMP
double parallel_sum(const double *array, int num_threads) {
    double sum = 0.0;
    int i;
    #pragma omp parallel for reduction(+:sum) num_threads(num_threads)
    for (i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    double *array = (double *)malloc(ARRAY_SIZE * sizeof(double));
    if (array == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    fill_array(array, ARRAY_SIZE);

    // Тестирование последовательной версии
    double start_time, end_time, total_time = 0.0;
    double seq_sum = 0.0;

    for (int run = 0; run < NUM_RUNS; run++) {
        start_time = omp_get_wtime();
        seq_sum = sequential_sum(array, ARRAY_SIZE);
        end_time = omp_get_wtime();
        total_time += (end_time - start_time);
    }
    printf("Последовательная сумма: %f\n", seq_sum);
    printf("Среднее время (последовательная версия): %f мс\n", (total_time / NUM_RUNS) * 1000);

    // Тестирование параллельной версии с разным количеством потоков
    int threads_list[] = {2, 4, 8, 16};
    int num_threads_options = sizeof(threads_list) / sizeof(threads_list[0]);

    for (int i = 0; i < num_threads_options; i++) {
        int num_threads = threads_list[i];
        total_time = 0.0;
        double par_sum = 0.0;

        for (int run = 0; run < NUM_RUNS; run++) {
            start_time = omp_get_wtime();
            par_sum = parallel_sum(array, ARRAY_SIZE, num_threads);
            end_time = omp_get_wtime();
            total_time += (end_time - start_time);
        }

        printf("Параллельная сумма (%d потоков): %f\n", num_threads, par_sum);
        printf("Среднее время (%d потоков): %f мс\n", num_threads, (total_time / NUM_RUNS) * 1000);
    }

    free(array);
    return 0;
}
