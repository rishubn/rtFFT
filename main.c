#include <stdio.h>
#include <complex.h>
#include "fft.h"


#define NUMELEMS(x) (sizeof(x) / sizeof((x)[0]))

int main()
{
    unsigned int x = 4;
    unsigned int y = 8;
    unsigned int z = 0xDEADBEEF;
    printf("%04x %04x\n", x, reverseBits(x));
    printf("%04x %04x\n", y, reverseBits(y));
    printf("%04x %04x\n", z, reverseBits(z));
    return 0;
}
