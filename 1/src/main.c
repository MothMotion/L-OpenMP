#include "omp_common.h"
#include "summ.h"
#include "random.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
  srand(time(NULL));
  arr_t array[ARRAY_SIZE];
  randomFill(array, ARRAY_SIZE);
  
  printf("OMP Threads number: %d\n\n", getThreadsNum());

  printf("Starting parallel summation...\n");

  clock_t start = clock();
  uint64_t summ = getSum(array, ARRAY_SIZE);
  clock_t end = clock();

  printf("Calculations finished.\n\nResult:%lu\nTime:%f\n", summ, (double)(end - start)/CLOCKS_PER_SEC);

  summ = 0;
  printf("\n===============\nStarting serial summation\n");
  start = clock();
  for(uint32_t i=0; i<ARRAY_SIZE; ++i)
    summ += array[i];
  end = clock();

  printf("Calculations finished.\n\nResult:%lu\nTime:%f\n", summ, (double)(end - start)/CLOCKS_PER_SEC);

  return 0;
}
