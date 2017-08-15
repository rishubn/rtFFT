#include "cbuffer.h"
#include <stdlib.h>


cbuffer_t* cb_create(size_t capacity)
{
    cbuffer_t* cb = malloc(sizeof(cbuffer_t));
    if(cb)
    {
        cb->capacity = capacity+1;
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
    free(cb);
    return E_SUCCESS;
}

int cb_read(cbuffer_t* cb, void* data, size_t datasize)
{
    if(cb->head == cb->tail)
    {
        return NULL;
    }
    memcpy(data, cb->tail, datasize);
    cb->tail = cb->tail + datasize;
    /*uint8_t* next = tail + count;
    next = &(*next & 7);
    void* data = cb->buffer[cb->tail];
    cb->tail = next;*/
    return E_SUCCESS;
}

int cb_write(cbuffer_t* cb, const void* data, size_t datasize)
{
    const uint8_t* src = data;
    const uint8_t* end = cb->buffer + cb->capacity;
    size_t i;
    for(i = 0; i < datasize; i += sizeof(uint8_t))
    {
        cb->head = cb->head + i;
        // wrap
        if(cb->head >= end)
        {
            cb->head = cb->buffer;
        }
        memcpy(cb->head, src + i, sizeof(uint8_t));
        printf("%02x\n", *(src+i));
    }
    return E_SUCCESS;
}











