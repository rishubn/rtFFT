#include <stdio.h>
#include <complex.h>
#include "fft.h"
#include "error.h"
#include "cbuffer.h"
#include <sndfile.h>
#include <math.h>
#define NUMELEMS(x) (sizeof(x) / sizeof((x)[0]))
#define INTMAX sizeof(uint_t)
int main()
{

    cbuffer_t* cb = cb_create(2*sizeof(dcomp_t));
   // printf("%zu", cb->capacity);
    if(cb == NULL)
    {
        eprintf(E_BUFFER_INIT_ERROR, "Failed to create buffer");
        return E_BUFFER_INIT_ERROR;
    }
    double data = 15.0;
    double data2 = 10.0;
    cb_write(cb, &data, sizeof(double));
   // cb_write(cb, &data2, sizeof(double));
    double dataout;
    size_t x = 0;
    printf("----\n");
    while(x < sizeof(double))
    {
        printf("%02x \n", *(cb->buffer + x));
        x+= sizeof(uint8_t);
    }
    cb_read(cb, &dataout, sizeof(double));
  //  printf("\n%f %f\n", creal(dataout), cimag(dataout));
    int y = cb_destroy(cb);
    return 0;
}


