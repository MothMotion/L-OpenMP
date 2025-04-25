#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

typedef enum { false, true } bool;

const int ARRAY_SIZE = 1000000; 

void PrintArray(int* array) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", array[i]);
    }
}

void QuickSort(bool threading, int thread_amount, int* array, int first_index, int last_index) {
    if (first_index < last_index) {
        int pivot = array[(first_index + last_index) / 2]; // Выбор среднего элемента
        int i = first_index;
        int j = last_index;
        int temp;

        while (i <= j) {
            while (array[i] < pivot) i++; // Элементы меньше среднего идут влево
            while (array[j] > pivot) j--; // Элементы больше среднего идут вправо
            if (i <= j) {
                temp = array[i];         // Обмен элементами
                array[i] = array[j];
                array[j] = temp;
                i++;
                j--;
            }
        }
    

        if (threading) { // Параллельно
            //#pragma omp parallel sections num_threads(thread_amount)
            //#pragma omp parallel num_threads(thread_amount)
            //#pragma omp single
            {  
                //#pragma omp section
                #pragma omp task shared(array)
                {
                    if (first_index < j) QuickSort(threading, thread_amount, array, first_index, j);
                }
            
                //#pragma omp section
                #pragma omp task shared(array)
                {
                    if (i < last_index) QuickSort(threading, thread_amount, array, i, last_index);
                }
            }
        } else { // Последовательно
            if (first_index < j) QuickSort(threading, thread_amount, array, first_index, j);
            if (i < last_index) QuickSort(threading, thread_amount, array, i, last_index);
        }
    }
}

bool CheckCorrectness(int* array) {
    for (int i = 0; i < ARRAY_SIZE-1; ++i) {
        if (array[i] > array[i+1]) {
            return false;
        }
    }
    return true;
}

void CopyArray(int* source_array, int* target_array) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        target_array[i] = source_array[i];
    }
}


void Task2(double* mean_time_sequential, double* mean_time_2_threads,
            double* mean_time_4_threads, double* mean_time_8_threads) {
    struct timespec start, end;
    double taken_time = 0.0;

    printf("Количетсво элементов в массиве: %d \n", ARRAY_SIZE);

    srand(time(0));

    int array[ARRAY_SIZE]; // Создаём и заполняем массив
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand() % 100;
    }

    int sorted_array[ARRAY_SIZE];
    CopyArray(array, sorted_array);
    //PrintArray(sorted_array); //для увеселения души


    // Последовательно
    clock_gettime(CLOCK_REALTIME, &start);
    QuickSort(false, 0, sorted_array, 0, ARRAY_SIZE-1);
    clock_gettime(CLOCK_REALTIME, &end);
    taken_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1e9;
    printf("Последовательно: занятое время: %f секунд\n", taken_time);
    *mean_time_sequential += taken_time;

    if (CheckCorrectness(sorted_array)) {
        printf("Сортировка успешна\n");
    } else {
        printf("Сортировка НЕ успешна\n");
    }
    //PrintArray(sorted_array);
    CopyArray(array, sorted_array);


    // 2 потока
    clock_gettime(CLOCK_REALTIME, &start);
    omp_set_num_threads(2);
    #pragma omp parallel
    {
      #pragma omp single
      QuickSort(true, 2, sorted_array, 0, ARRAY_SIZE-1);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    taken_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1e9;
    printf("Параллельно 2 потока: занятое время: %f секунд\n", taken_time);
    *mean_time_2_threads += taken_time;

    if (CheckCorrectness(sorted_array)) {
        printf("Сортировка успешна\n");
    } else {
        printf("Сортировка НЕ успешна\n");
    }
    CopyArray(array, sorted_array);


    // 4 потока
    clock_gettime(CLOCK_REALTIME, &start);
    omp_set_num_threads(4);
    #pragma omp parallel
    {
      #pragma omp single
      QuickSort(true, 4, sorted_array, 0, ARRAY_SIZE-1);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    taken_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1e9;
    printf("Параллельно 4 потока: занятое время: %f секунд\n", taken_time);
    *mean_time_4_threads += taken_time;

    if (CheckCorrectness(sorted_array)) {
        printf("Сортировка успешна\n");
    } else {
        printf("Сортировка НЕ успешна\n");
    }
    CopyArray(array, sorted_array);


    // 8 потоков
    clock_gettime(CLOCK_REALTIME, &start);
    omp_set_num_threads(8);
    #pragma omp parallel
    {
      #pragma omp single
      QuickSort(true, 8, sorted_array, 0, ARRAY_SIZE-1);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    taken_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1e9;
    printf("Параллельно 8 потоков: занятое время: %f секунд\n", taken_time);
    *mean_time_8_threads += taken_time;

    if (CheckCorrectness(sorted_array)) {
        printf("Сортировка успешна\n\n");
    } else {
        printf("Сортировка НЕ успешна\n\n");
    }


} 

int main() {
    double mean_time_sequential = 0.0;
    double mean_time_2_threads = 0.0;
    double mean_time_4_threads = 0.0;
    double mean_time_8_threads = 0.0;
    int runs = 100;
    
    for (int i = 0; i < runs; ++i) {
        
        Task2(&mean_time_sequential, &mean_time_2_threads, 
            &mean_time_4_threads, &mean_time_8_threads);
    }

    mean_time_sequential = mean_time_sequential / runs;
    mean_time_2_threads = mean_time_2_threads / runs;
    mean_time_4_threads = mean_time_4_threads / runs;
    mean_time_8_threads = mean_time_8_threads / runs;

    printf("Среднее время выполнения (%d выполнений):\nПоследовательно:%f\nПараллельно 2 потока:%f\nПараллельно 4 потока:%f\nПараллельно 8 потоков:%f\n",
            runs, mean_time_sequential, mean_time_2_threads, mean_time_4_threads, mean_time_8_threads);
    
}
