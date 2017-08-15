#include <stdio.h>
#include <math.h>
#include <float.h>
#include "minunit.h"
#include "../fft.h"
#include "../cbuffer.h"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


int tests_run = 0;

static char* test_checkPowerTwo()
{
    unsigned int x = 256;
    unsigned int y = 65536;
    unsigned int z = 6532;

    mu_assert("error checkPower2(256) != true", checkPowerTwo(x));
    mu_assert("error checkPower2(65536) != true", checkPowerTwo(y));
    mu_assert("error checkPower2(6532) != false", !checkPowerTwo(z));
    return 0;
}

static char* test_fastlog2()
{
    unsigned int x = 4;
    unsigned int y = 16777216;
    unsigned int z = 4096;

    mu_assert("error fastlog2(x) != 2", fastlog2(x));
    mu_assert("error fastlog2(y) != 24", fastlog2(y));
    mu_assert("error fastlog2(z) != 12", fastlog2(z));
    return 0;
}

static char* test_reverseBitsWithShift()
{
    unsigned int x = 0xBCD178;
    unsigned int y = 0x91F;
    unsigned int z = 0xDEADBEEF;

    unsigned int x_expected = 0x1E8B3D;
    unsigned int y_expected = 0xF89;
    unsigned int z_expected = 0xF77DB57B;
    mu_assert("error reverseBits(0xBCD178) != 0x1E8B3D", reverseBits(x) >> (INTSIZE - 24)== x_expected);
    mu_assert("error reverseBits(0x91F) != 0xF89", reverseBits(y) >> (INTSIZE - 12)== y_expected);
    mu_assert("error reverseBits(0xDEADBEEF) != 0xF77DB57B", reverseBits(z) >> (INTSIZE - 32) == z_expected);
    return 0;
}
static char* test_bitReverseCopy()
{
    dcomp_t x[8];
    dcomp_t y[9];
    dcomp_t expected[8];
    expected[0] = 0.0;
    expected[1] = 4.0;
    expected[2] = 2.0;
    expected[3] = 6.0;
    expected[4] = 1.0;
    expected[5] = 5.0;
    expected[6] = 3.0;
    expected[7] = 7.0;
    
    for(int i = 0; i < 8; i++)
    {
        dcomp_t z = i;
        x[i] = z;
    }
    bitReverseCopy(x,y,8); 
    
    for(int i = 0; i < 8; i++)
    {
        mu_assert("Expected array did not match actual for bitReverseCopy", creal(expected[i] == creal(y[i])));
    }
    return 0;
}
// Tests cb_create and destroy
static char* test_cb_create()
{
    size_t expected_capacity = 2*sizeof(uint8_t);
    cbuffer_t* cb = cb_create(2*sizeof(uint8_t));
    mu_assert("cb_create returned a null buffer", cb != NULL);
    mu_assert("cb_create did not create expected capacity", cb->capacity == expected_capacity);
    mu_assert("cb_create did not initialize internal buffer", cb->buffer != NULL);
    mu_assert("cb_create did not initialize buffer head", cb->head == cb->buffer);
    mu_assert("cb_create did not initialize buffer tail", cb->tail == cb->buffer);
    cb_destroy(cb);
    return 0;
}
// Writes data to the buffer and ensures its stored correctly.
static char* test_cb_write()
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
    mu_assert("cb_write did not write correctly", *(p++) == a);
    mu_assert("cb_write did not write correctly", *(p++) == 0xCC);
    mu_assert("cb_write did not write correctly", *(p++) == 0xBB);
    mu_assert("cb_write did not write correctly", *(p++) == d);
    
    // Write more bytes to test wrap.
    cb_write(cb, &e, sizeof(uint8_t));
    p = cb->buffer;
    mu_assert("cb_write did not wrap correctly", *(p) == e);
    cb_write(cb, &bc, sizeof(uint16_t));
    cb_write(cb, &bc, sizeof(uint16_t));
    mu_assert("cb_write did not wrap correctly", *(p) == 0xBB);
    
    return 0;
}

// Writes some test data to the buffer and reads it
static char* test_cb_read()
{
    cbuffer_t* cb = cb_create(sizeof(uint32_t));
    uint8_t a = 0xAA;
    uint16_t bc = 0xBBCC;
    uint8_t d = 0xDD;
    uint8_t e = 0xEE;
    mu_assert("Buffer not initialized to empty", cb_read(cb, NULL, 0));

    // Write four bytes of data to the buffer
    cb_write(cb, &a, sizeof(uint8_t));
    cb_write(cb, &bc, sizeof(uint16_t));
    cb_write(cb, &d, sizeof(uint8_t));
    

}
//Tests FFT on a shifted impulse. Expected data provided by MATLAB
static char* test_iterativeFFT()
{
    dcomp_t expected[8];
    dcomp_t input[8];
    dcomp_t output[8];
    input[0] = 0;
    input[1] = 1;
    input[2] = 0;
    input[3] = 0;
    input[4] = 0;
    input[5] = 0;
    input[6] = 0;
    input[7] = 0;

    expected[0] = 1;
    expected[1] = 0.707107 - 0.707107*I;
    expected[2] = 0-1*I;
    expected[3] = -0.707107 - 0.707107*I;
    expected[4] = -1;
    expected[5] = -0.707107 + 0.707107*I;
    expected[6] = 1*I;
    expected[7] = 0.707107 + 0.707107*I;;

    iterativeFFT(input, output, 8);
    int i = 0;
    while(i < 8)
    {
        mu_assert("Calculated result did not match expected", cabs(expected[i] - output[i]) < 0.000001);
        i++;
    }
    return 0;
}
static char* all_tests()
{
    mu_run_test(test_reverseBitsWithShift);
    mu_run_test(test_fastlog2);
    mu_run_test(test_checkPowerTwo);
    mu_run_test(test_bitReverseCopy);
    mu_run_test(test_iterativeFFT);
    mu_run_test(test_cb_create);
    mu_run_test(test_cb_write);
    return 0;
}



int main()
{
    char* result = all_tests();
    if(result != 0)
    {
        printf("%s%s\n",KRED, result);
    }
    else
    {
        printf("%sALL TESTS PASSED\n",KGRN);
    }
    printf("%sTests run: %d\n",KBLU,tests_run);
    return result != 0;
}
