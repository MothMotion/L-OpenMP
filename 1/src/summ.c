#include "summ.h"

#include <stdint.h>

#include <omp.h>

const uint64_t pSum(const arr_t array[], const uint32_t size) {
  uint64_t result = 0;

  #pragma omp parallel for reduction(+:result)
  for(uint32_t i=0; i<size; ++i)
    result += array[i];
  //{ 
    //uint64_t sub_sum = 0;

    //#pragma omp for reduction(+:result)
    //for(uint32_t i=0; i<size; ++i)
    //  result += array[i];

    //#pragma omp atomic
    //result += sub_sum;
  //}
  return result;
}

const uint64_t sSum(const arr_t array[], const uint32_t size) {
  uint64_t result = 0;

  for(uint32_t i=0; i<size; ++i)
    result += array[i];
  return result;
}
