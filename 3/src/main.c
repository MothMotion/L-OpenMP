#include "operations.h"
#include "random.h"
#include "timer.h"
#include "omp_common.h"

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  srand(time(NULL));

  arr_t array1[ARRAY_SIZE],
          array2[ARRAY_SIZE],
          out_array[ARRAY_SIZE];
  double timer;

  randomFill(array1, ARRAY_SIZE);
  randomFill(array2, ARRAY_SIZE);

  printf("OMP Threads number: %d\n\n", getThreadsNum());

  printf("Addition, parallel.\n");
  GETTIME(pAddArray, timer, array1, array2, out_array, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Addition, serial.\n");
  GETTIME(sAddArray, timer, array1, array2, out_array, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Substraction, parallel.\n");
  GETTIME(pSubArray, timer, array1, array2, out_array, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Substraction, serial.\n");
  GETTIME(sSubArray, timer, array1, array2, out_array, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Multiplication, parallel.\n");
  GETTIME(pAddArray, timer, array1, array2, out_array, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Multiplication, serial.\n");
  GETTIME(sAddArray, timer, array1, array2, out_array, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Division, parallel.\n");
  GETTIME(pDivArray, timer, array1, array2, out_array, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  printf("Division, serial.\n");
  GETTIME(sDivArray, timer, array1, array2, out_array, ARRAY_SIZE);
  printf("Time: %f\n\n", timer);

  return 0;
}
