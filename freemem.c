// freeman.c - implementation of function freemem
// CSE374 HW6, Yunsi Mou
// Mar 2, 2017

#include <stdlib.h>
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"
#define HEADER_SIZE 16

// Return the block of storage at location p to the pool of available
// free storage.
void freemem(void* p) {
  if (p == NULL) {
    return;
  }

  check_heap();  // comment this line later

  // the free node pointer to the block include header
  free_node * startaddr = (free_node *) p - 1;
  // update the total free in the free list
  insert_block(startaddr);
}
