//se si vuole usare ricordarsi di compilare con rand.h e non .cc
#ifndef myLib_h
#define myLib_h

#include <cstdlib>

template <class T>T rand_range (T min, T max);
template <class T>T rand_CLT (T xMin, T xMax, int tries);
#include "rand.cc"
#endif
