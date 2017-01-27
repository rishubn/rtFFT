//FFT Library
#include "fft.h"
#include "error.h"
#include <limits.h>

//bit hack magic
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

//Assumes size is a power of 2
uint_t generateBitMask(uint_t size)
{
    uint_t r = MultiplyDeBruijnBitPosition2[(uint_t)(size * 0x077CB531U) >> 27];
    return (1 << r) - 1;
}

uint_t reverseBits(uint_t num)
{
    num = ((num * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;    
    return num;
}

int bitReverseCopy(dcomp_t input[], dcomp_t output[], size_t length)
{
    if(checkPowerTwo(length) == E_INVALID_INPUT || checkPowerTwo(length) == 0)
    {
        eprintf(E_INVALID_INPUT, "Given array length is not a power of 2");
    }
    uint_t bitMask = generateBitMask(length);
    for(uint_t i = 0; i < length; i++)
    {
        output[reverseBits(i) & bitMask] = input[i];
    }
    return E_SUCCESS;
}





