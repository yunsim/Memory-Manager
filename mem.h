// mem.h
// The header file of the memory management project, containing
// declarations of public functions in the memory manager,
// giving an interface of our getmem/freemem package

// CSE374 HW6
// Yirou Luo
// Mar 2, 2017

#ifndef MEM_H
#define MEM_H

#include <inttypes.h>
#include <stdio.h>

// Return a pointer to a new block of storage at least size bytes of memory.
void* getmem(uintptr_t size);

// Return the block of storage at location p to the pool of available
// free storage. If p is NULL, the call of freemem has no effect
void freemem(void* p);

// Store statistics about the current state of the memory manager
// total_size: total amount of storage in bytes acquired by memory
//             manager so far.
// total_free: total amount of storage in bytes that is currently
//             stored in the free list
// n_total_blocks: total number of individual blocks currently
//                 stored in the free list.
void get_mem_stats(uintptr_t* total_size,
  uintptr_t* total_free, uintptr_t* n_free_blocks);

// Print a formatted listing on file f showing the blocks on the free list.
void print_heap(FILE * f);

// Return all the blocks back to malloc
// void freeall();

#endif
