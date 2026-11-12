#include <stdio.h>
#include "smem.h"
#include <stdlib.h>
#include <string.h>
uint8_t *ptrs[64] = {0};
size_t sizes[64] = {0};
int main(void)
{
    srand(42);
    for (int iter = 0; iter < 10000; iter++) {
        int idx = rand() % 64;
        uint8_t tag = (uint8_t)((idx % 250) + 1);

        if (ptrs[idx] == NULL) {
            size_t sz = (rand() % 512) + 1;
            ptrs[idx] = smalloc(sz);
            if (!ptrs[idx]) {
                fprintf(stderr, "smalloc failed at iter %d\n", iter);
                exit(1);
            }
            memset(ptrs[idx], tag, sz);
            sizes[idx] = sz;
        } else {
            for (size_t i = 0; i < sizes[idx]; i++) {
                if (ptrs[idx][i] != tag) {
                    fprintf(stderr, "CORRUPTION at iter %d, slot %d, byte %zu/%zu: expected 0x%02x, got 0x%02x\n",
                            iter, idx, i, sizes[idx], tag, ptrs[idx][i]);
                    exit(1);
                }
            }

            if (rand() % 3 == 0) {
                size_t new_sz = (rand() % 512) + 1;
                size_t min_sz = sizes[idx] < new_sz ? sizes[idx] : new_sz;
                uint8_t *p = srealloc(ptrs[idx], new_sz);
                if (!p) {
                    fprintf(stderr, "srealloc failed at iter %d\n", iter);
                    exit(1);
                }
                for (size_t i = 0; i < min_sz; i++) {
                    if (p[i] != tag) {
                        fprintf(stderr, "SREALLOC LOSS at iter %d, slot %d, byte %zu\n", iter, idx, i);
                        exit(1);
                    }
                }
                memset(p, tag, new_sz);
                ptrs[idx] = p;
                sizes[idx] = new_sz;
            } else {
                sfree(ptrs[idx]);
                ptrs[idx] = NULL;
                sizes[idx] = 0;
            }
        }
    }

    for (int i = 0; i < 64; i++) {
        if (ptrs[i]) {
            uint8_t tag = (uint8_t)((i % 250) + 1);
            for (size_t j = 0; j < sizes[i]; j++) {
                if (ptrs[i][j] != tag) {
                    fprintf(stderr, "FINAL CORRUPTION at slot %d, byte %zu\n", i, j);
                    exit(1);
                }
            }
            sfree(ptrs[i]);
        }
    }
    printf("All 10000 iterations passed with zero corruption!\n");}
