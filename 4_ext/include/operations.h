#pragma once
#ifndef OPERATIONS
#define OPERATIONS

#define ARRAY_SIZE 150
#define DIMENSIONS 4
#define arr_t uint8_t

#define CYCLES 1

#include <stdint.h>

void pMultiDim(void* inp_array1, void* inp_array2, void* out_array,
               const uint32_t size, const uint32_t dim, const uint8_t operation);
void sMultiDim(void* inp_array1, void* inp_array2, void* out_array,
               const uint32_t size, const uint32_t dim, const uint8_t operation);

void init(void** array, const uint32_t size, const uint32_t dim);

void deinit(void** array, const uint32_t size, const uint32_t dim);

void pAddArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void pSubArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void pMulArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void pDivArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);

void sAddArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void sSubArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void sMulArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void sDivArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);

enum Operations {
  pAdd = 0,
  pSub,
  pMul,
  pDiv,

  sAdd,
  sSub,
  sMul,
  sDiv
};

#endif // !OPERATIONS
