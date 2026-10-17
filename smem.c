#include <stdio.h>
#include <stdint.h>
#include "smem.h"
#include <unistd.h>
#include <string.h>

#define METADATA_SIZE sizeof(metadata)

metadata *startBlock = NULL;

metadata *get_free_block(size_t size)
{
    metadata *block = startBlock; 
    while(block != NULL)
    {
        if(block->size >= size && block->free == 1)
            return block;
        block = block->next;
    }
    return NULL;
}

metadata *get_last_list(void)
{
    metadata *p = startBlock;
    while(p->next != NULL)
        p = p->next;
    return p;
}

metadata *request_space(size_t size)
{
    metadata *block = sbrk(size + METADATA_SIZE);
    if(block == (void *) -1)
        return NULL;
    block->size = size;
    block->free = 0;
    block->next = NULL;
    return block;
}

void *smalloc(size_t size)
{
    if(size <= 0)
        return NULL;
    if(startBlock == NULL)
    {
        startBlock = request_space(size);
        if(startBlock == NULL)
            return NULL;
        return (startBlock + 1);
    }
    else
    {
        metadata *block = get_free_block(size);
        if(block != NULL)
            block->free = 0;
        else
        {
           block = request_space(size); 
           if(block == NULL)
               return NULL;
           metadata *last = get_last_list();
           last->next = block; 
        }
        return (block + 1);
    }
    
}

void sfree(void *p)
{
    if(p == NULL)
        return;
    metadata *block = ((metadata *)p - 1);
    block->free = 1;
}

void *scalloc(size_t num, size_t size)
{
    size_t csize = num * size;
    void *p = smalloc(csize);
    if(p == NULL)
        return NULL;
    memset(p, 0, csize);
    return p;
}

void *srealloc(void *p, size_t size)
{
    if(size <= 0) 
    {
        sfree(p);
        return NULL;
    }
    if(p == NULL)
        return smalloc(size);
    if(((metadata *)p - 1)->size >= size)
        return p;
    else
    {
        void *temp;
        temp = smalloc(size);
        if(temp == NULL)
            return NULL;
        memcpy(temp, p, ((metadata *)p - 1)->size);
        sfree(p);
        return temp;
    }
}
