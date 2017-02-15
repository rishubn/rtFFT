#include <stdio.h>
#include <complex.h>
#include "fft.h"
#include "error.h"
#include <math.h>
#define NUMELEMS(x) (sizeof(x) / sizeof((x)[0]))
#define INTMAX sizeof(uint_t)
int main()
{
    dcomp_t x[8192];
    dcomp_t y[8192];
    for(int i = 0; i < 8192; i++)
    {
        dcomp_t z = csin(2*3.14159*i*100/8192); //+ 0*I;
        x[i] = z;
    }
    iterativeFFT(x,y,8192);
    for(int i =0; i < 8192; i++)
    {
        printf("%f + %f*i\n", creal(y[i]), cimag(y[i]));
    }
    eprintf(E_SUCCESS,"HELLO");
    return 0;
}
