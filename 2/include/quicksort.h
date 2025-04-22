#pragma once
#ifndef QUICKSORT
#define QUICKSORT

#define ARRAY_SIZE 100000
#define arr_t uint16_t

#include <stdint.h>

void pQSort(arr_t array[], const uint32_t start, const uint32_t end);

void sQSort(arr_t array[], const uint32_t start, const uint32_t end);

const uint8_t checkArray(const arr_t array[], const uint32_t size);

void swap(arr_t* op1, arr_t* op2);

#endif
