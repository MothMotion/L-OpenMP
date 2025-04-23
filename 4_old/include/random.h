#pragma once
#ifndef RANDOM
#define RANDOM

#define MAX_RAND 256

#include "operations.h"

#include <stdint.h>

void randomFill(arr_t array[], const uint32_t size);
void randomMultiDim(void** array, const uint32_t size, const uint32_t dim);

#endif
