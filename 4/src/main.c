#include "operations.h"
#include "timer.h"

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  srand(time(NULL));

  void *array1,
       *array2,
       *out_array;
  double timer;

  printf("Initializing...\n");
 
  // parallize this, i dare you
  GETTIME(init, timer, &array1, ARRAY_SIZE, DIMENSIONS); 
  printf("arr1 done, time: %f\n", timer);
  GETTIME(init, timer, &array2, ARRAY_SIZE, DIMENSIONS);
  printf("arr2 done, time: %f\n", timer);
  GETTIME(init, timer, &out_array, ARRAY_SIZE, DIMENSIONS); 
  printf("out done, time: %f\n\n", timer);

  printf("Addition, parallel.\n");
  #pragma omp parallel
  {
    #pragma omp single 
    { GETTIME(pMultiDim, timer, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, pAdd); }
  }
  printf("Time: %f\n\n", timer); 

  printf("Addition, serial.\n");
  GETTIME(sMultiDim, timer, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, sAdd);
  printf("Time: %f\n\n", timer);

  printf("Substraction, parallel.\n");
  #pragma omp parallel
  {
    #pragma omp single
    { GETTIME(pMultiDim, timer, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, pSub); }
  }
  printf("Time: %f\n\n", timer);

  printf("Substraction, serial.\n");
  GETTIME(sMultiDim, timer, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, sSub);
  printf("Time: %f\n\n", timer);

  printf("Multiplication, parallel.\n");
  #pragma omp parallel
  {
    #pragma omp single
    { GETTIME(pMultiDim, timer, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, pMul); }
  }
  printf("Time: %f\n\n", timer);

  printf("Multiplication, serial.\n");
  GETTIME(sMultiDim, timer, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, sMul);
  printf("Time: %f\n\n", timer);

  printf("Division, parallel.\n");
  #pragma omp parallel
  {
    #pragma omp single
    { GETTIME(pMultiDim, timer, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, pDiv); }
  }
  printf("Time: %f\n\n", timer);

  printf("Division, serial.\n");
  GETTIME(sMultiDim, timer, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, sDiv);
  printf("Time: %f\n\n", timer);

  printf("Deleting arrays...\n"); 
  deinit(&array1, ARRAY_SIZE, DIMENSIONS); 
  deinit(&array2, ARRAY_SIZE, DIMENSIONS);
  deinit(&out_array, ARRAY_SIZE, DIMENSIONS);
  printf("Done.\n");

  return 0;
}
