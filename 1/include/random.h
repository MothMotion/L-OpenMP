#pragma once
#ifndef RANDOM
#define RANDOM

#define MAX_RAND 256

#include "summ.h"

#include <stdint.h>

void randomFill(uint8_t array[], const uint32_t size);

#endif
