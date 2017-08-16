#include "cbuffer.h"
#include <stdlib.h>


cbuffer_t* cb_create(const size_t capacity)
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
        cb->count = 0;
        cb->end = cb->buffer + cb->capacity;
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
    if(cb->count == 0)
    {
        return E_BUFFER_EMPTY;
    }
    else if((cb->count - datasize) >= INT_MAX)
    {
        return E_UNDERFLOW;
    }
    else 
    {
        cb->count -= datasize;
    }
    uint8_t* dst = data;
    size_t i;
    for(i = 0; i < datasize; i++)
    {
        // wrap
        if(cb->tail >= cb->end)
        {
            cb->tail = cb->buffer;
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
    size_t i;
    cb->count = MIN(cb->count + datasize, cb->capacity);
    for(i = 0; i < datasize; i++)
    {
        // wrap
        if(cb->head >= cb->end)
        {
            cb->head = cb->buffer;
        }
        memcpy(cb->head, src, sizeof(uint8_t));
        src++;
        cb->head++;
    }
    
    return E_SUCCESS;
}
int cb_write_dcompt(cbuffer_t* cb, const dcomp_t* data)
{
    return cb_write(cb, data, sizeof(dcomp_t));
}

int cb_read_dcompt(cbuffer_t* cb, dcomp_t* data)
{
    return cb_read(cb, data, sizeof(dcomp_t));
}