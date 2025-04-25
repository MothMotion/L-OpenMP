#pragma once
#ifndef RANDOM
#define RANDOM

#define MAX_RAND 256

#include "operations.h"

#include <stdint.h>

void randomFill(arr_t array[], const uint32_t size);
void randomizeMat(arr_t* array[], const uint32_t sizeX, const uint32_t sizeY);

#endif
