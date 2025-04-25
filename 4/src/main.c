#include "operations.h"
#include "timer.h"
#include "omp_common.h"
#include "random.h"

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  srand(time(NULL));

  arr_t *array1[ARRAY_SIZE],
        *array2[ARRAY_SIZE],
        *out_array[ARRAY_SIZE];
  double t_init_arr1=0, t_init_arr2=0,
         ptadd=0, ptsub=0, ptmul=0, ptdiv=0,
         stadd=0, stsub=0, stmul=0, stdiv=0;

  printf("Settings:\n\tOMP Threads: %d\n\tArray sizes: %dx%d\n\tCycles: %d\n\n",
         getThreadsNum(), ARRAY_SIZE, ARRAY_SIZE, CYCLES); 

  init(array1, ARRAY_SIZE, ARRAY_SIZE);
  init(array2, ARRAY_SIZE, ARRAY_SIZE);
  init(out_array, ARRAY_SIZE, ARRAY_SIZE);

  printf("Starting calculations...\n");
  for(uint32_t i=0; i<CYCLES; ++i) {
    ADDTIME_COR(randomizeMat, t_init_arr1, CYCLES, array1, ARRAY_SIZE, ARRAY_SIZE);
    ADDTIME_COR(randomizeMat, t_init_arr2, CYCLES, array2, ARRAY_SIZE, ARRAY_SIZE); 

    ADDTIME_COR(pAddArray, ptadd, CYCLES, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
    ADDTIME_COR(sAddArray, stadd, CYCLES, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);

    ADDTIME_COR(pSubArray, ptsub, CYCLES, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
    ADDTIME_COR(sSubArray, stsub, CYCLES, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);

    ADDTIME_COR(pMulArray, ptmul, CYCLES, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
    ADDTIME_COR(sMulArray, stmul, CYCLES, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);

    ADDTIME_COR(pDivArray, ptdiv, CYCLES, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
    ADDTIME_COR(sDivArray, stdiv, CYCLES, array1, array2, out_array, ARRAY_SIZE, ARRAY_SIZE);
  }

  printf("Calculations done.\np - parallel, s - serial\nTime for:\n\tRandom arr1: %f\t\tRandom arr2: %f\n\
\n\tpAdd: %f\t\tsAdd: %f\n\tpSub: %f\t\tsSub: %f\n\tpMul: %f\t\tsMul: %f\n\tpDiv: %f\t\tsDiv: %f\n",
         t_init_arr1, t_init_arr2, ptadd, stadd, ptsub, stsub, ptmul, stmul, ptdiv, stdiv);

  deinit(array1, ARRAY_SIZE);
  deinit(array2, ARRAY_SIZE);
  deinit(out_array, ARRAY_SIZE);

  return 0;
}
