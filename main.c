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

    cbuffer_t* cb = cb_create(sizeof(uint32_t));
    uint8_t a = 0xAA;
    uint16_t bc = 0xBBCC;
    uint8_t d = 0xDD;
    uint8_t e = 0xEE;

    // Write four bytes of data to the buffer
    cb_write(cb, &a, sizeof(uint8_t));
    cb_write(cb, &bc, sizeof(uint16_t));
    cb_write(cb, &d, sizeof(uint8_t));

    uint8_t* p = cb->buffer;
    p++;
    p++;
  //  printf("\n%f %f\n", creal(dataout), cimag(dataout));
    int y = cb_destroy(cb);
    return 0;
}


