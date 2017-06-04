// get_mem_stats.c
// implementation of function get_mem_stats

// CSE374 HW6
// Yirou Luo
// Mar 2, 2017

#include <stdio.h>
#include <inttypes.h>
#include "mem_impl.h"

// Store statistics about the current state of the memory manager
// total_size: total amount of storage in bytes acquired by memory
//             manager so far.
// total_free: total amount of storage in bytes that is currently
//             stored in the free list
// n_total_blocks: total number of individual blocks currently
//                 stored in the free list.
void get_mem_stats(uintptr_t* total_size,
                   uintptr_t* total_free, uintptr_t* n_free_blocks) {
  *total_size = gl_total_size;

  free_node * curr = free_list;
  while (curr != NULL) {
    *total_free += curr -> size;
    (*n_free_blocks)++;
    curr = curr -> next;
  }
  return;
}
