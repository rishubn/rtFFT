#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <stdio.h>

enum error_codes
{
    E_SUCESS = 0,
    E_INVALID_INPUT = -1,
}

typedef error_codes error_t;

struct errordesc {
    int code;
    char* message;
} errordesc = {
    { E_SUCCESS, "No error" },
    { E_INVALID_INPUT, "Invalid input" },
};


#endif
