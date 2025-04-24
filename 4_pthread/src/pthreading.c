#include "pthreading.h"
#include "operations.h"

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

void* pThreadWrap(void* args) {
  pThreadArgs* pArgs = (pThreadArgs*) args;
  void (*process)(arr_t[], arr_t[], arr_t[], const uint32_t);
  switch(pArgs->oper) {
    //case pAdd : return pAddArray(pArgs->in1, pArgs->in2, pArgs->out, pArgs->size);
    case pDiv : process = pDivArray; break;
  }
  if(process)
    for(uint32_t i=pArgs->from; i<pArgs->to; ++i)
      process(pArgs->in1[i], pArgs->in2[i], pArgs->out[i], ARRAY_SIZE);
  return NULL;
}

void pThreading(arr_t* inp1[], arr_t* inp2[], arr_t* out[],
                const uint32_t sizeX, const uint32_t sizeY, const uint8_t operation,
                const uint16_t threads_amount) {
  uint16_t th_size = min(threads_amount, MAX_THREADS);
  pthread_t threads[th_size];
  pThreadArgs thread_args[th_size];
  uint32_t distr = sizeX / th_size;

  for(uint16_t i=0; i < th_size; ++i) {
    thread_args[i].in1 = inp1;
    thread_args[i].in2 = inp2;
    thread_args[i].out = out;
    thread_args[i].from = i*distr;
    thread_args[i].to = (i+1)*distr;
    thread_args[i].oper = operation;
    //thread_args[j] = create_args(inp1[i], inp2[i], out[i], sizeY, operation);

    pthread_create(&threads[i], NULL, pThreadWrap, &thread_args[i]);
  }

  for(uint16_t i=0; i < th_size; ++i)
    pthread_join(threads[i], NULL);
}
