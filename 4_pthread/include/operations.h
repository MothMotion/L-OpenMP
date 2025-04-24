#pragma once
#ifndef OPERATIONS
#define OPERATIONS

#define ARRAY_SIZE 120000
#define arr_t uint8_t

#include <stdint.h>

void pAddArray(arr_t* inp_array1[], arr_t* inp_array2[], arr_t* out_array[], const uint32_t sizeX, const uint32_t sizeY);
void pSubArray(arr_t* inp_array1[], arr_t* inp_array2[], arr_t* out_array[], const uint32_t sizeX, const uint32_t sizeY);
void pMulArray(arr_t* inp_array1[], arr_t* inp_array2[], arr_t* out_array[], const uint32_t sizeX, const uint32_t sizeY);
void pDivArray(arr_t inp_array1[], arr_t inp_array2[], arr_t out_array[], const uint32_t size);

void sAddArray(arr_t* inp_array1[], arr_t* inp_array2[], arr_t* out_array[], const uint32_t sizeX, const uint32_t sizeY);
void sSubArray(arr_t* inp_array1[], arr_t* inp_array2[], arr_t* out_array[], const uint32_t sizeX, const uint32_t sizeY);
void sMulArray(arr_t* inp_array1[], arr_t* inp_array2[], arr_t* out_array[], const uint32_t sizeX, const uint32_t sizeY);
void sDivArray(arr_t* inp_array1[], arr_t* inp_array2[], arr_t* out_array[], const uint32_t sizeX, const uint32_t sizeY);

void init(arr_t* array[], const uint32_t sizeX, const uint32_t sizeY);
void deinit(arr_t* array[], const uint32_t size);

#endif // !OPERATIONS
