#pragma once
#include <stdint.h>
#ifndef PTHREADING_H
#define PTHREADING_H

#define MAX_THREADS 32

#define min(a, b) ((a) < (b) ? (a) : (b))

#include "operations.h"

#include "stdint.h"

typedef enum : uint8_t {
  pAdd = 0, pSub,
  pMul, pDiv,

  sAdd, sSub,
  sMul, sDiv
} eOperation;

typedef struct {
  arr_t** in1;
  arr_t** in2;
  arr_t** out;

  uint32_t from;
  uint32_t to;

  uint8_t oper;
} pThreadArgs;

pThreadArgs create_args(arr_t input1[], arr_t input2[], arr_t out[],
                        const uint32_t size, const uint8_t operation);

void pThreading(arr_t* input1[], arr_t* input2[], arr_t* out[],
                const uint32_t sizeX, const uint32_t sizeY, const uint8_t operation,
                const uint16_t threads_amount);



void* pThreadWrap(void* args);

#endif // PTHREADING_H
