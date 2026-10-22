#ifndef SMALLOC_H
#define SMALLOC_H

#include <stdint.h>
#include <stdbool.h>

typedef struct metadata
{
    struct metadata *next;
    size_t size;
    bool free;
} metadata;

void *smalloc(size_t size);
void sfree(void *p);
void *scalloc(size_t nums, size_t size);
void *srealloc(void *p, size_t size);
void see_list(void);
#endif
