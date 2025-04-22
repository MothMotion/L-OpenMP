#include "random.h"

#include <stdint.h>
#include <stdlib.h>

void randomFill(arr_t array[], const uint32_t size) {
  //#pragma omp for <- bs
  for(uint32_t i=0; i<size; ++i)
    array[i] = rand()%MAX_RAND;
}

void randomMultiDim(void** arr, const uint32_t size, const uint32_t dim) {
  if(dim < 1)
    return;

  if(dim == 1)
    return randomFill((uint8_t*)*arr, size);
 
  for(uint32_t i=0; i<size; ++i)
    //#pragma omp task shared(arr) <- wont work lol
    randomMultiDim(&arr[i], size, dim-1);
}
