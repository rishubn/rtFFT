#ifndef FFT_H_INCLUDED
#define FFT_H_INCLUDED

#include <complex.h>
#include <stddef.h>
#include <limits.h>

#define INTSIZE sizeof(uint_t) * CHAR_BIT

typedef unsigned int uint_t;
typedef double complex dcomp_t;

int checkPowerTwo(uint_t n);
uint_t reverseBits(uint_t n);
uint_t fastlog2(uint_t n);
int bitReverseCopy(dcomp_t input[], dcomp_t output[], size_t length);


#endif
