#include "error.h"
#include <stdio.h>
struct errordesc error_descriptions[] = 
{ {E_SUCCESS, "No Error"},
  {E_INVALID_INPUT, "Invalid input"} };

void eprintf(error_t errnum, const char* desc)
{
    printf("%s : %s",error_descriptions[-errnum].message, desc);
}
