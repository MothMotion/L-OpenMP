#include "quicksort.h"
#include "random.h"
#include "timer.h"
#include "omp_common.h"

#include <stdio.h>

int main() {
  arr_t arr[ARRAY_SIZE];
  double timer;
  randomFill(arr, ARRAY_SIZE);

  printf("OMP Threads number: %d\n\n", getThreadsNum());

  printf("Sorting, parallel.\n");
  #pragma omp parallel
  {
    #pragma omp single
    {
      GETTIME(pQSort, timer, arr, 0, ARRAY_SIZE-1);
    }
  }
  printf("Complete. Correctness: %d; Time: %f\n\n", checkArray(arr, ARRAY_SIZE), timer);

  randomFill(arr, ARRAY_SIZE);

  printf("Sorting, serial.\n");
  GETTIME(sQSort, timer, arr, 0, ARRAY_SIZE-1);
  printf("Complete. Correctness: %d; Time: %f\n", checkArray(arr, ARRAY_SIZE), timer);

  return 0;
}
