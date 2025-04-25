#include "operations.h"
#include "timer.h"
#include "omp_common.h"

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  srand(time(NULL));

  void *array1,
       *array2,
       *out_array;
  double ptadd=0, ptsub=0, ptmul=0, ptdiv=0,
         stadd=0, stsub=0, stmul=0, stdiv=0, timer;

  printf("Settings:\n\tOMP Threads: %d\n\tArray sizes: %d\n\tDimensions: %d\n\tCycles: %d\n\n",
         getThreadsNum(), ARRAY_SIZE, DIMENSIONS, CYCLES);

  printf("Initializing...\n");
 
  // parallize this, i dare you
  //#pragma omp parallel
  {
    //#pragma omp single // slow first even slower next two
    //#pragma omp parallel sections num_threads(3) // same as above
    {
      //#pragma omp section// shared(array1)
      {
        GETTIME(init, timer, &array1, ARRAY_SIZE, DIMENSIONS);
        printf("arr1 done, time: %f\n", timer);
      }
      //#pragma omp section// shared(array2)
      {
        GETTIME(init, timer, &array2, ARRAY_SIZE, DIMENSIONS);
        printf("arr2 done, time: %f\n", timer);
      }
      //#pragma omp section// shared(out_array)
      {
        GETTIME(init, timer, &out_array, ARRAY_SIZE, DIMENSIONS); 
        printf("out done, time: %f\n", timer);
      }
    }
  }

  printf("Starting calculations...\n");
  for(uint32_t i=0; i<CYCLES; ++i) {
    #pragma omp parallel
    #pragma omp single
    {ADDTIME_COR(pMultiDim, ptadd, CYCLES, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, pAdd);}
    ADDTIME_COR(sMultiDim, stadd, CYCLES, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, sAdd);

    #pragma omp parallel
    #pragma omp single
    {ADDTIME_COR(pMultiDim, ptsub, CYCLES, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, pSub);}
    ADDTIME_COR(sMultiDim, stsub, CYCLES, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, sSub);

    #pragma omp parallel
    #pragma omp single
    {ADDTIME_COR(pMultiDim, ptmul, CYCLES, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, pMul);}
    ADDTIME_COR(sMultiDim, stmul, CYCLES, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, sMul);

    #pragma omp parallel
    #pragma omp single
    {ADDTIME_COR(pMultiDim, ptdiv, CYCLES, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, pDiv);}
    ADDTIME_COR(sMultiDim, stdiv, CYCLES, array1, array2, out_array, ARRAY_SIZE, DIMENSIONS, sDiv);
  }

  printf("Calculations done.\np - parallel, s - serial\nTime for:\
\n\tpAdd: %f\t\tsAdd: %f\n\tpSub: %f\t\tsSub: %f\n\tpMul: %f\t\tsMul: %f\n\tpDiv: %f\t\tsDiv: %f\n",
         ptadd, stadd, ptsub, stsub, ptmul, stmul, ptdiv, stdiv);

  printf("Deleting arrays...\n");
  // wont parallize bc same reasons as init
  deinit(&array1, ARRAY_SIZE, DIMENSIONS); 
  deinit(&array2, ARRAY_SIZE, DIMENSIONS);
  deinit(&out_array, ARRAY_SIZE, DIMENSIONS);
  printf("Done.\n");

  return 0;
}
