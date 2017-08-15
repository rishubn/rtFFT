#ifndef CBUFFER_H_INCLUDED
#define CBUFFER_H_INCLUDED

/* A byte-addressable FIFO Circular buffer implementation in C
 * Data is written to at the head and read from the tail
 */
#include <stddef.h>
#include <stdint.h>
#include "error.h"
#include "fft.h"
typedef struct {
    uint8_t* buffer;
    uint8_t* head;
    uint8_t* tail;
    size_t capacity;
} cbuffer_t;

//Create a circle buffer of size capacity
cbuffer_t* cb_create(size_t capacity);

//free the memory used by a circle buffer
int cb_destroy(cbuffer_t* cb);

//Read data from the tail pointer to tail+datasize
//Returns E_UNDERFLOW on read underflow (Tail moves past the head); resets tail
//Return E_BUFFER_EMPTY when there is nothing to read
//Returns E_SUCCESS on read success
int cb_read(cbuffer_t* cb, void* data, size_t datasize);

//Write data from the head pointer to head+datasize. Wraps if needed
//Warning: This function does not check if the head writes over the tail; overflows can happen
//Returns E_SUCCESS on write success
int cb_write(cbuffer_t* cb, const void* data, size_t datasize);

#endif
