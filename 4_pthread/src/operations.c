#include "operations.h"
#include "random.h"

#include <omp.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

void pAddArray(arr_t* arr1[], arr_t* arr2[], arr_t* out[], const uint32_t sizeX, const uint32_t sizeY) { 
  //#pragma omp parallel for
  for(uint32_t i=0; i < sizeX; ++i) {
    #pragma omp task firstprivate(i)
    {
      //#pragma omp parallel for
      for(uint32_t j=0; j < sizeY; ++j)
        out[i][j] = arr1[i][j] + arr2[i][j];
    }
  }
}

void pSubArray(arr_t* arr1[], arr_t* arr2[], arr_t* out[], const uint32_t sizeX, const uint32_t sizeY) { 
  #pragma omp parallel for collapse(2) shared(arr1, arr2, out, sizeX, sizeY)
  for(uint32_t i=0; i < sizeX; ++i)
    for(uint32_t j=0; j < sizeY; ++j)
      out[i][j] = arr1[i][j] - arr2[i][j];
}

void pMulArray(arr_t* arr1[], arr_t* arr2[], arr_t* out[], const uint32_t sizeX, const uint32_t sizeY) {
  //#pragma omp parallel for shared(arr1, arr2, out, sizeX, sizeY)
  #pragma omp parallel for default(none) shared(arr1, arr2, out, sizeX, sizeY)
  for(uint32_t i=0; i < sizeX; ++i)
    for(uint32_t j=0; j < sizeY; ++j)
      out[i][j] = arr1[i][j] * arr2[i][j];
}

void pDivArray(arr_t arr1[], arr_t arr2[], arr_t out[], const uint32_t size) {
  for(uint32_t i=0; i<size; ++i)
    if(arr2[i])
      out[i] = arr1[i] / arr2[i];
    else out[i] = arr1[i];
  /*
    for(uint32_t i=0; i < sizeX; ++i)
    for(uint32_t j=0; j < sizeY; ++j)
      if(arr2[i][j])
        out[i][j] = arr1[i][j] / arr2[i][j];
      else out[i][j] = arr1[i][j]; // i dont give a f
  */
}



void sAddArray(arr_t* arr1[], arr_t* arr2[], arr_t* out[], const uint32_t sizeX, const uint32_t sizeY) {
  for(uint32_t i=0; i < sizeX; ++i) 
    for(uint32_t j=0; j < sizeY; ++j)
      out[i][j] = arr1[i][j] + arr2[i][j];
}

void sSubArray(arr_t* arr1[], arr_t* arr2[], arr_t* out[], const uint32_t sizeX, const uint32_t sizeY) {
  for(uint32_t i=0; i < sizeX; ++i)
    for(uint32_t j=0; j < sizeY; ++j)
      out[i][j] = arr1[i][j] - arr2[i][j];
}

void sMulArray(arr_t* arr1[], arr_t* arr2[], arr_t* out[], const uint32_t sizeX, const uint32_t sizeY) {
  for(uint32_t i=0; i < sizeX; ++i) 
    for(uint32_t j=0; j < sizeY; ++j)
      out[i][j] = arr1[i][j] * arr2[i][j];
}

void sDivArray(arr_t* arr1[], arr_t* arr2[], arr_t* out[], const uint32_t sizeX, const uint32_t sizeY) {
  #pragma omp parallel for collapse(2) shared(arr1, arr2, out, sizeX, sizeY)
  for(uint32_t i=0; i < sizeX; ++i)
    for(uint32_t j=0; j < sizeY; ++j)
      if(arr2[i][j])
        out[i][j] = arr1[i][j] / arr2[i][j];
      else out[i][j] = arr1[i][j]; // i STILL dont give a f
}


void init(arr_t* arr[], const uint32_t sizeX, const uint32_t sizeY) {
  #pragma omp parallel for
  for(uint32_t i=0; i<sizeX; ++i) {
    arr[i] = malloc(sizeY * sizeof(arr_t));
    //randomFill(arr[i], sizeY);
  }
}

void deinit(arr_t* arr[], const uint32_t size) {
  //#pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    free(arr[i]);
}
