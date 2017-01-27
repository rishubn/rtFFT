#ifndef FFT_H_INCLUDED
#define FFT_H_INCLUDED

#include <complex.h>
#include <stddef.h>

typedef unsigned int uint_t;
typedef double complex dcomp_t;

int checkPowerTwo(uint_t n);
uint_t reverseBits(uint_t n);
uint_t generateBitMask(uint_t size);
int bitReverseCopy(dcomp_t input[], dcomp_t output[], size_t length);


#endif
