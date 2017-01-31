#include <stdio.h>
#include "minunit.h"
#include "../fft.h"
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
static char* all_tests()
{
    mu_run_test(test_reverseBitsWithShift);
    mu_run_test(test_fastlog2);
    mu_run_test(test_checkPowerTwo);
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
