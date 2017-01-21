#include "fft.h"

#define CHAR_BIT 8*sizeof(char)


bool checkPowerTwo(uint_t n)
{
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

