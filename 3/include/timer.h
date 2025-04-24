#pragma once
#ifndef TIMER
#define TIMER

#include <time.h>

#define GETTIME(func, time_var, ...) {\
  struct timespec start, end;\
  clock_gettime(CLOCK_REALTIME, &start);\
  func(__VA_ARGS__);\
  clock_gettime(CLOCK_REALTIME, &end);\
  time_var = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1e9;\
}

#endif
