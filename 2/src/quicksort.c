#include "quicksort.h"
#include <stdint.h>

void pQSort(arr_t* arr, const uint32_t start, const uint32_t end) {
  if(end == -1 || start >= end)
    return;

  uint32_t i = start, j = end;

  while(i<j) {
    while(i<j && arr[i] <= arr[start+(end-start)/2]) ++i;
    while(i<j && arr[j] >= arr[start+(end-start)/2]) --j;

    swap(&arr[i], &arr[j]);
  }

  #pragma omp task shared(arr)
  pQSort(arr, start, j-1);
  #pragma omp task shared(arr)
  pQSort(arr, j+1, end); 
}

void sQSort(arr_t* arr, const uint32_t start, const uint32_t end) {
  if(end == -1 || start >= end)
    return;

  uint32_t i = start, j = end;

  while(i<j) {
    while(i<j && arr[i] <= arr[start+(end-start)/2]) ++i;
    while(i<j && arr[j] >= arr[start+(end-start)/2]) --j;

    swap(&arr[i], &arr[j]);
  }

  sQSort(arr, start, j-1);
  sQSort(arr, j+1, end);
}

const uint8_t checkArray(const arr_t* arr, const uint32_t size) {
  uint8_t err = 0;
  #pragma omp parallel for 
  for(uint32_t i=0; i < size-1; ++i)
    if(arr[i] > arr[i+1])
      err = 1;
  return err;
}

void swap(arr_t* op1, arr_t* op2) {
  *op1 ^= *op2;
  *op2 ^= *op1;
  *op1 ^= *op2;
}
