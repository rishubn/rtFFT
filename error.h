//This component is designed to make error handling and processing easier
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

void eprintf(error_t errnum, const char* desc);

#endif
