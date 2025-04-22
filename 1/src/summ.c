#include "summ.h"

#include <stdint.h>

#include <omp.h>

const uint64_t getSum(const arr_t array[], const uint32_t size) {
  uint64_t result = 0;

  #pragma omp parallel
  { 
    uint64_t sub_sum = 0;

    #pragma omp for
    for(uint32_t i=0; i<size; ++i)
      sub_sum += array[i];

    #pragma omp atomic
    result += sub_sum;
  }
  return result;
}
