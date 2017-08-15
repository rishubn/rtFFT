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

    cbuffer_t* cb = cb_create(2*sizeof(uint8_t));
   // printf("%zu", cb->capacity);
    if(cb == NULL)
    {
        eprintf(E_BUFFER_INIT_ERROR, "Failed to create buffer");
        return E_BUFFER_INIT_ERROR;
    }
    uint8_t data = 0xAB;
    uint8_t data2 = 0xCD;
    cb_write(cb, &data, sizeof(uint8_t));
    cb_write(cb, &data2, sizeof(uint8_t));
    // cb_write(cb, &data2, sizeof(uint8_t));
    // cb_write(cb, &data, sizeof(uint8_t));
    // cb_write(cb, &data2, sizeof(uint8_t));
    // uint16_t data3 = 0xFE10;
    // cb_write(cb, &data3, sizeof(uint16_t));
    uint8_t dataout;
    int x = 0;
    printf("----\n");
    uint8_t* p = cb->buffer;
    while(x < 2*sizeof(uint8_t))
    {
        printf("%02x \n", *(p++));
        x++;
    }
    
    cb_read(cb, &dataout, sizeof(uint8_t));
    printf("%02x \n", dataout);
    cb_read(cb, &dataout, sizeof(uint8_t));
    printf("%02x \n", dataout);
    cb_read(cb, &dataout, sizeof(uint8_t));
    printf("%02x \n", dataout);
  //  printf("\n%f %f\n", creal(dataout), cimag(dataout));
    int y = cb_destroy(cb);
    return 0;
}


