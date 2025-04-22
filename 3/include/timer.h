#pragma once
#ifndef TIMER
#define TIMER

#include <time.h>

#define GETTIME(func, time_var, ...) {\
  clock_t start = clock();\
  func(__VA_ARGS__);\
  clock_t end = clock();\
  time_var = (double)(end-start)/CLOCKS_PER_SEC;\
}

#endif
