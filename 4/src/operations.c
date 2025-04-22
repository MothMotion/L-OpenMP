#include "operations.h"
#include "random.h"

#include <omp.h>
#include <stdint.h>
#include <stdlib.h>

void pMultiDim(void* arr1, void* arr2, void* out,
               const uint32_t size, const uint32_t dim, const uint8_t operation) { 
  if(dim < 1) // why
    return;

  if(dim == 1)
    switch(operation) {
      case pAdd : return pAddArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case pSub : return pSubArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case pMul : return pMulArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case pDiv : return pDivArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);

      // why do you need these?
      case sAdd : return sAddArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case sSub : return sSubArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case sMul : return sMulArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case sDiv : return sDivArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      
      default: return; // what are you doing?
    }
 
  for(uint32_t i=0; i<size; ++i)
    #pragma omp task shared(arr1, arr2, out)
    pMultiDim(((void**)arr1)[i], ((void**)arr2)[i], ((void**)out)[i], size, dim-1, operation); 
}

void sMultiDim(void* arr1, void* arr2, void* out,
               const uint32_t size, const uint32_t dim, const uint8_t operation) { 
  if(dim < 1) // just why
    return;

  if(dim == 1)
    switch(operation) {
      // is there some higher meaning?
      case pAdd : return pAddArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case pSub : return pSubArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case pMul : return pMulArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case pDiv : return pDivArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
 
      case sAdd : return sAddArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case sSub : return sSubArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case sMul : return sMulArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      case sDiv : return sDivArray((arr_t*)arr1, (arr_t*)arr2, (arr_t*)out, size);
      
      default: return; // what
    }

  for(uint32_t i=0; i<size; ++i)
    sMultiDim(((void**)arr1)[i], ((void**)arr2)[i], ((void**)out)[i], size, dim-1, operation);
}

void init(void** array, const uint32_t size, const uint32_t dim) { 
  if(dim < 1) // why you keep doing this?
    return; 

  if(dim == 1) {
    *array = malloc(size * sizeof(arr_t));
    //#pragma omp task
    randomFill(*array, size);
    return;
  }
  *array = malloc(size * sizeof(void*)); 

  //#pragma omp parallel for // only slowing down
  //#pragma omp single
  for(uint32_t i=0; i<size; ++i) {
    //#pragma omp task // fast but malloc corrupted top size
    {
      void* temp; 
      //#pragma omp task // super fast but strange behaviour 
      init(&temp, size, dim-1);
      ((void**)*array)[i] = temp;
    }
  } 
}

void deinit(void** array, const uint32_t size, const uint32_t dim) {
  if(dim < 1) // just stop
    return; 

  if(dim > 1) { 
    for(uint32_t i=0; i<size; ++i)
      //#pragma omp task shared(array) <- get owned, wont work 
      deinit(&((void**)*array)[i], size, dim-1);
  }
  free(*array);
}



void pAddArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  #pragma omp parallel for 
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] + arr2[i];
}

void pSubArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  #pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] - arr2[i];
}

void pMulArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  #pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] * arr2[i];
}

void pDivArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  #pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    if(arr2[i])
      out[i] = arr1[i] / arr2[i];
    else out[i] = arr1[i]; // i still dont give a f
}



void sAddArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] + arr2[i];
}

void sSubArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] - arr2[i];
}

void sMulArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] * arr2[i];
}

void sDivArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) { 
  for(uint32_t i=0; i<size; ++i)
    if(arr2[i])
      out[i] = arr1[i] / arr2[i];
    else out[i] = arr1[i]; // do i REALLY need to repeat myself?
}
