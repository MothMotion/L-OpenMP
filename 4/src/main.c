#include "operations.h"
#include "timer.h"
#include "omp_common.h"

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  srand(time(NULL));

  arr_t *array1[ARRAY_SIZE],
        *array2[ARRAY_SIZE],
        *out_array[ARRAY_SIZE];
  double timer;

  printf("Initialization...\n");

  GETTIME(init, timer, array1, ARRAY_SIZE, ARRAY_SIZE);
  printf("array1 done. time: %f\n", timer);
  GETTIME(init, timer, array2, ARRAY_SIZE, ARRAY_SIZE);
  printf("array2 done. time: %f\n", timer);
  GETTIME(init, timer, out_array, ARRAY_SIZE, ARRAY_SIZE);
  printf("out done. time: %f\n\n", timer);



  printf("OMP Threads number: %d\n\n", getThreadsNum());

  printf("Addition, parallel.\n");
  #pragma omp parallel
  {
    #pragma omp single
    {
      GETTIME(pAddArray, timer, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
    }
  }
  printf("Time: %f\n\n", timer);

  printf("Addition, serial.\n");
  GETTIME(sAddArray, timer, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Substraction, parallel.\n");
  GETTIME(pSubArray, timer, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Substraction, serial.\n");
  GETTIME(sSubArray, timer, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Multiplication, parallel.\n");
  GETTIME(pAddArray, timer, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Multiplication, serial.\n");
  GETTIME(sAddArray, timer, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Division, parallel.\n");
  GETTIME(pDivArray, timer, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Division, serial.\n");
  GETTIME(sDivArray, timer, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  deinit(array1, ARRAY_SIZE);
  deinit(array2, ARRAY_SIZE);
  deinit(out_array, ARRAY_SIZE);

  return 0;
}
