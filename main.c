#include <stdio.h>
#include <complex.h>
#include "fft.h"

#define NUMELEMS(x) (sizeof(x) / sizeof((x)[0]))

int main()
{
    for(int i = 0; i < 32; i++)
    {
        uint_t bitMask = generateBitMask(32);
        printf("0x%08x, 0x%08x 0x%08x \n", i, reverseBits(i) & bitMask, bitMask);
        


    }
    return 0;
}
