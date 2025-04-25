#include "quicksort.h"
#include "random.h"
#include "timer.h"
#include "omp_common.h"

#include <stdint.h>
#include <stdio.h>

int main() {
  arr_t arr[ARRAY_SIZE];
  double ptimer=0, stimer=0;

  printf("Settings:\n\tOMP Threads: %d\n\tArray size: %d\n\tCycles: %d\n\n",
         getThreadsNum(), ARRAY_SIZE, CYCLES);
  
  for(uint32_t i=0; i < CYCLES; ++i) {
    randomFill(arr, ARRAY_SIZE); 
    #pragma omp parallel
    {
      #pragma omp single
      { ADDTIME_COR(pQSort, ptimer, CYCLES, arr, 0, ARRAY_SIZE-1); }
    }

    randomFill(arr, ARRAY_SIZE);
    ADDTIME_COR(sQSort, stimer, CYCLES, arr, 0, ARRAY_SIZE-1);
  }

  printf("Calculations finished.\n\tParallel time: %f\n\tSerial time: %f\n",
         ptimer, stimer);

  return 0;
}
