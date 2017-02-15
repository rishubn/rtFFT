//This component is designed to make error handling and processing easier

#include <stdio.h>


#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

typedef enum error_codes
{
    E_SUCCESS = 0,
    E_INVALID_INPUT = -1,
} error_t;

struct errordesc {
    int code;
    char* message;
}; 

static void eprintf(error_t errnum, const char* desc);

static struct errordesc error_descriptions[] = 
{ {E_SUCCESS, "No Error"},
  {E_INVALID_INPUT, "Invalid input"} };

//Function Definitions

void eprintf(error_t errnum, const char* desc)
{
    printf("%s : %s",error_descriptions[-errnum].message, desc);
}
#endif
