#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define META_SIZE sizeof(struct metadata)

typedef struct metadata 
{
    struct metadata *next;
    size_t size;
    bool free;
} metadata;

metadata *start_block = NULL;

metadata *find_free_block(struct metadata **last, size_t size)
{
    struct metadata *curr = start_block;
    while(curr != NULL)
    {
        if(curr->free == 1 && curr->size >= size)
        {
            return curr;
        }
        *last = curr;
        curr = curr->next;
    }
    return NULL;
}

metadata *request_space(struct metadata *last, size_t size)
{
    struct metadata *block;
    block = sbrk(size + META_SIZE);
    if(block == (void*) -1)
        return NULL;
    if(last != NULL)
        last->next = block;
    block->size = size;
    block->free = 0;
    block->next = NULL;

    return block;
}

void *smalloc(size_t size)
{
    if(size <= 0) 
        return NULL;
    struct metadata *block;
    if(start_block == NULL)
    {
        block = request_space(NULL, size);
        if(block == NULL)
            return NULL;
        start_block = block;
    }
    else
    {
        struct metadata *last = start_block;
        block = find_free_block(&last, size);
        if(block == NULL)
        {
            block = request_space(last, size);
            if(block == NULL)
                return NULL;
        }
        else
        {
            block->free = 0;
        }
    }

    return (block + 1);
}

struct metadata *get_block_meta(void *p)
{
    return (metadata*)p - 1;
}

void sfree(void *p)
{
   struct metadata *block = get_block_meta(p); 
   block->free = 1;
}
int main(void)
{
    int *a = smalloc(5 * sizeof(int));
    for(int i = 0; i < 5; i++)
        a[i] = i;
    for(int i = 0; i < 5; i++)
        printf("%d ", a[i]); 
    sfree(a);
    return 0;
}
