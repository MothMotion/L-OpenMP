#include "omp_common.h"
#include "summ.h"
#include "random.h"
#include "timer.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
  srand(time(NULL));
  arr_t array[ARRAY_SIZE];
  double ptimer = 0, stimer = 0;

  printf("Settings:\n\tOMP Threads: %d\n\tArray Size: %d\n\tCycles: %d\n\n",
         getThreadsNum(), ARRAY_SIZE, CYCLES);

  for(uint32_t i=0; i<CYCLES; ++i) {
    randomFill(array, ARRAY_SIZE); 

    ADDTIME_COR(pSum, ptimer, CYCLES, array, ARRAY_SIZE); 
    ADDTIME_COR(sSum, stimer, CYCLES, array, ARRAY_SIZE);
  }

  printf("Calculations finished.\n\tParallel time: %f\n\tSerial time: %f\n", ptimer, stimer);

  return 0;
}
