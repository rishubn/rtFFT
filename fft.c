//FFT Library
#include "fft.h"
#include "error.h"
#include <limits.h>
#include <stddef.h>

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
int bitReverseCopy(dcomp_t input[], dcomp_t output[], size_t length)
{
    bool isLengthPowerTwo = checkPowerTwo(length);
    if(isLengthPowerTwo == false || isLengthPowerTwo == E_INVALID_INPUT)
    {
        return E_INVALID_INPUT;
    }
    for(uint_t i = 0; i < length; i++)
    {
        output[reverseBits(i)] = input[i];
    }
    return E_SUCCESS;
}





