# smem
The memory allocation family written from scratch in C.
The name comes from scratch and the short for memory: smem

## Disclaimer

This project is more proof of concept than actual stable, solid, working code.
Use the actual memory allocation family provided by `stdlib.h`. Trust me, it's better. 

## How it works

The `smem` memory allocation family uses `sbrk` to extend the heap. As a way to keep
track of every chunk and their respective size and freeness, `smem` utilises a singly linked list.
Because of this, the amount of bytes which are allocated are actually: `requested size + the size of each node`.
Moreover, `smem` reuses free chunks by means of splitting and for every
`sfree()` call, if consecutive chunks are free, they will be merged together.

## Limitations

 * Not thread-safe;
 * POSIX only;
 * Heap never shrinks;
 * Linear O(n) complexity;
 * No alignment;
 * Compiler optimization flags may break something.


## Functions 

 * `smalloc(size_t size)`
 * `scalloc(size_t nums, size_t size)`
 * `srealloc(void *p, size_t size)`
 * `sfree(void *p)`

## Usage

Simply copy `smem.h` and `smem.c` into your project, include `"smem.h"`, and compile alongside your source files.
 
