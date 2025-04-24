#pragma once
#ifndef OPERATIONS
#define OPERATIONS

#define ARRAY_SIZE 2500000
#define arr_t uint8_t

#include <stdint.h>

void pAddArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void pSubArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void pMulArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void pDivArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);

void sAddArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void sSubArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void sMulArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);
void sDivArray(const arr_t inp_array1[], const arr_t inp_array2[], arr_t out_array[], const uint32_t size);

#endif // !OPERATIONS
