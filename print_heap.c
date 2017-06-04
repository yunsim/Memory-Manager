// print_heap.c
// implementation of function print_heap

// CSE374 HW6
// Yirou Luo
// Mar 2, 2017

#include <stdint.h>
#include <stdio.h>
#include "mem_impl.h"

#define HEADER_SIZE 16

free_node * free_list;

// Print a formatted listing on file f showing the blocks on the free list.
void print_heap(FILE * f) {
  if (f == NULL) {
    fprintf(stderr, "No such file.\n");
    return;
  }

  free_node * curr = free_list;
  while (curr != NULL) {
    fprintf(f, "Block address = 0x%016" PRIxPTR ", length = %lu\n",
            (uintptr_t)curr, (curr -> size + HEADER_SIZE));
    curr = curr -> next;
  }

  fprintf(f, "\n");
  return;
}
