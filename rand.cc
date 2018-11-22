#include "rand.h"

template <class T>T rand_range (T min, T max)
{
  return rand() / (T)RAND_MAX * (max-min) + min;
}

template <class T>T rand_CLT (T xMin, T xMax, int tries)
{
  T x = 0;

  for (int i = 0; i < tries; i++)
    x += rand_range(xMin, xMax);

  return x/tries;
}
