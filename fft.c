#include <stdio.h>
//#include <complex.h>

//#define NUMELEMS(x) (sizeof(x) / sizeof((x)[0]))
#include "fft.h"

#define CHAR_BIT 8*sizeof(char)

unsigned int reverseBits(unsigned int num)
{
    unsigned int  num_bits  = sizeof(num) * CHAR_BIT;
    unsigned int reverse_num = 0;
    int i;
    for (i = 0; i < num_bits; i++)
    {
        if((num & (1 << i)))
           reverse_num |= 1 << ((num_bits - 1) - i);  
   }
    return reverse_num;
}

