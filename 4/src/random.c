#include "random.h"

#include <stdint.h>
#include <stdlib.h>
#include <omp.h>

void randomFill(arr_t array[], const uint32_t size) {
  #pragma omp parallel for shared(array)
  for(uint32_t i=0; i<size; ++i)
    array[i] = rand()%MAX_RAND;
}

void randomizeMat(arr_t* array[], const uint32_t sizeX, const uint32_t sizeY) {
  #pragma omp parallel for collapse(2) shared(array)
  for(uint32_t i=0; i<sizeX; ++i)
    for(uint32_t j=0; j<sizeY; ++j)
      array[i][j] = 5; //rand()%MAX_RAND; // too slow
}
