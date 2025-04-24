#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

typedef enum { false, true } bool;

const int ARRAY_SIZE = 2000000; 

void PrintArray(int* array) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", array[i]);
    }
}

unsigned long int ComputeSum(bool threading, int thread_amount, int* array) {
    unsigned long int sum = 0;

    if (threading) { // Параллельно
        #pragma omp parallel num_threads(thread_amount)
        {   
            #pragma omp master
            {
                printf("Количество потоков: %d \n", omp_get_num_threads());
            }

            #pragma omp for reduction (+:sum)
            for (int i = 0; i < ARRAY_SIZE; ++i) {
                sum += array[i];
            }
        }
    } else { // Последовательно
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            sum += array[i];
        }
    }

    return sum;
}

int main() {
    struct timespec begin, end;
    unsigned long int sum = 0;

    printf("Количетсво элементов в массиве: %d \n", ARRAY_SIZE);

    srand(time(0));
    int array[ARRAY_SIZE]; // Создаём и заполняем массив
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand() % 100;
    }

    //PrintArray(array); //для увеселения души

    // Последовательно
    clock_gettime(CLOCK_REALTIME, &begin);
    sum = ComputeSum(false, 0, array);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Последовательно: занятое время: %f секунд, результат: %.0f \n", 
        (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_nsec - begin.tv_nsec)/1e9, (double)sum);

    // 2 потока
    clock_gettime(CLOCK_REALTIME, &begin);
    sum = ComputeSum(true, 2, array);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Параллельно 2 потока: занятое время: %f секунд, результат: %.0f \n", 
        (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_nsec - begin.tv_nsec)/1e9, (double)sum);

    // 4 потока
    clock_gettime(CLOCK_REALTIME, &begin);
    sum = ComputeSum(true, 4, array);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Параллельно 4 потока: занятое время: %f секунд, результат: %.0f \n", 
        (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_nsec - begin.tv_nsec)/1e9, (double)sum);

    // 8 потоков
    clock_gettime(CLOCK_REALTIME, &begin);
    sum = ComputeSum(true, 8, array);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Параллельно 8 потоков: занятое время: %f секунд, результат: %.0f \n", 
        (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_nsec - begin.tv_nsec)/1e9, (double)sum);

    return 0;
}