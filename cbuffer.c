#include "cbuffer.h"
#include <stdlib.h>


cbuffer_t* cb_create(size_t capacity)
{
    cbuffer_t* cb = malloc(sizeof(cbuffer_t));
    if(cb)
    {
        cb->capacity = capacity;
        cb->buffer = malloc(cb->capacity);
        if(!cb->buffer)
        {
            free(cb);
            return NULL;
        }
        cb->head = cb->buffer;
        cb->tail = cb->buffer;
    }
    return cb;
}

int cb_destroy(cbuffer_t* cb)
{
    free(cb->buffer);
    cb->buffer = NULL;
    free(cb);
    cb = NULL;
    return E_SUCCESS;
}

int cb_read(cbuffer_t* cb, void* data, size_t datasize)
{
    if(cb->head == cb->tail)
    {
        return E_BUFFER_EMPTY;
    }
    const uint8_t* end = cb->buffer + cb->capacity;
    const uint8_t* dst = data;
    const uint8_t* start = cb->tail;
    size_t i;
    for(i = 0; i < datasize; i++)
    {
        // wrap
        if(cb->tail >= end)
        {
            cb->tail = cb->buffer;
        }
        if(cb->tail == cb->head)
        {
            cb->tail = start; //reset the tail when underflow occurs
            return E_UNDERFLOW;
        }
        memcpy(dst, cb->tail, sizeof(uint8_t));
        cb->tail++;
        dst++;
    }
    return E_SUCCESS;
}

int cb_write(cbuffer_t* cb, const void* data, size_t datasize)
{
    const uint8_t* src = data;
    const uint8_t* end = cb->buffer + cb->capacity;
    size_t i;
    for(i = 0; i < datasize; i++)
    {
        // wrap
        if(cb->head >= end)
        {
            cb->head = cb->buffer;
        }
        memcpy(cb->head, src, sizeof(uint8_t));
        src++;
        cb->head++;
    }
    
    return E_SUCCESS;
}











