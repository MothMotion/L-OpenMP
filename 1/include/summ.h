#pragma once
#ifndef FUNC
#define FUNC

#include <stdint.h>

#define ARRAY_SIZE 2000000
#define arr_t uint8_t

#define CYCLES 1000

const uint64_t pSum(const arr_t array[], const uint32_t size);
const uint64_t sSum(const arr_t array[], const uint32_t size);

#endif
