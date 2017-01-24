//FFT Library
#include "fft.h"
#include "error.h"
#include <limits.h>

bool checkPowerTwo(uint_t n)
{
    if(n > UINT_MAX){
        return E_INVALID_INPUT;
    }
    return ((n & (n -1)) == 0);
}


uint_t reverseBits(uint_t num)
{
    uint_t  num_bits  = sizeof(num) * CHAR_BIT;
    uint_t reverse_num = 0;
    int i;
    for (i = 0; i < num_bits; i++)
    {
        if((num & (1 << i)))
           reverse_num |= 1 << ((num_bits - 1) - i);  
   }
    return reverse_num;
}

dcomp_t* bitReverseCopy(dcomp_t input[], size_t length)
{
    dcomp_t reversed[length];
    for(uint_t i = 0; i < length; i++)
    {
        reversed[reverseBits(i)] = input[i];
    }
    return reversed;
}





