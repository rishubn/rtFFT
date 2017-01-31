//FFT Library
#include "fft.h"
#include "error.h"
#include <limits.h>

//bit hack magic - table for finding log(n)
static const int MultiplyDeBruijnBitPosition2[32] = 
{
      0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};

int checkPowerTwo(uint_t n)
{
    if(n > UINT_MAX){
        return E_INVALID_INPUT;
    }
    return ((n & (n -1)) == 0);
}

//Assumes n is a power of two
uint_t fastlog2(uint_t n)
{
    return MultiplyDeBruijnBitPosition2[(uint_t)(n * 0x077CB531U) >> 27];
}
//From bit twiddiling hacks
uint_t reverseBits(uint_t num)
{
    num = ((num >> 1) & 0x55555555) | ((num & 0x55555555) << 1);
    // swap consecutive pairs
    num = ((num >> 2) & 0x33333333) | ((num & 0x33333333) << 2);
    // swap nibbles ... 
    num = ((num >> 4) & 0x0F0F0F0F) | ((num & 0x0F0F0F0F) << 4);
    // swap bytes
    num = ((num >> 8) & 0x00FF00FF) | ((num & 0x00FF00FF) << 8);
    // swap 2-byte long pairs
    num = ( num >> 16             ) | ( num               << 16);
    return num;
}

int bitReverseCopy(dcomp_t input[], dcomp_t output[], size_t length)
{
    if(checkPowerTwo(length) == E_INVALID_INPUT || checkPowerTwo(length) == 0)
    {
        eprintf(E_INVALID_INPUT, "Given array length is not a power of 2");
        return E_INVALID_INPUT;
    }
    if(length < 256)
    {
        eprintf(E_INVALID_INPUT, "Input array must contain >255 elements");
        return E_INVALID_INPUT;
    }
    uint_t wordlength = fastlog2(length);
    for(uint_t i = 0; i < length; i++)
    {
        output[reverseBits(i) >> (INTSIZE - wordlength)] = input[i];
    }
    return E_SUCCESS;
}





