// getmem.c
// implementation of function getmem

// CSE374 HW6
// Yirou Luo
// Mar 2, 2017

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "mem_impl.h"

#define HEADER_SIZE 16
#define DEFAULT_BLOCK 8000
#define MAX_GAP 112


// Pre-Declaration of divide
free_node * divide(free_node * addr, free_node * target, uintptr_t size);

// Return a pointer to a new block of storage at least size bytes of memory.
void* getmem(uintptr_t size) {
  if (size <= 0) {
    return NULL;
  }
  check_heap();  // comment this line later

  // Avoid small blocks:
  if (size < MAX_GAP) {
    return getmem(MAX_GAP);
  }

  // align the size on an 16-byte boundary
  if (size % HEADER_SIZE != 0) {
    size = (size / HEADER_SIZE + 1) * HEADER_SIZE;
  }

  // if free_list is null, malloc!
  if (free_list == NULL) {
    if (size > DEFAULT_BLOCK) {  // gives a block of given size
      uintptr_t blockpt = (uintptr_t) malloc(size + HEADER_SIZE);
      gl_total_size += (size + HEADER_SIZE);

      ((free_node *) blockpt) -> size = size;
      return (void *) (blockpt + HEADER_SIZE);
    }

    // else: size <= DEFAULT_BLOCK
    // malloc a block of default size as the first block of free list
    free_list = (free_node *) malloc(DEFAULT_BLOCK + HEADER_SIZE);
    gl_total_size += (DEFAULT_BLOCK + HEADER_SIZE);

    free_list -> size = DEFAULT_BLOCK;
    free_list -> next = NULL;
  }

  // free_list is not null:
  free_node * addr = 0;  // the address of header of the block we will return
  if ((free_list -> size) > size) {  // the first block is already enough
    if (free_list -> size - (size) < MAX_GAP) {
      // gives the first block:
      addr = free_list;
      free_list = free_list -> next;
    } else {  // divide the first block
      addr = divide(addr, free_list, size);
    }
  } else {
    // the first block is not enough, find another block!
    free_node * current = free_list;
    while (current -> next != NULL && current -> next -> size < size) {
      current = current -> next;
    }
    if (current -> next == NULL) {  // no block is enough. Malloc!
      if (size > DEFAULT_BLOCK) {  // malloc a really big block
        uintptr_t blockpt = (uintptr_t) malloc(size + HEADER_SIZE);
        gl_total_size += (size + HEADER_SIZE);
        ((free_node *) blockpt) -> size = size;
        ((free_node *) blockpt) -> next = NULL;
        return (void *) (blockpt + HEADER_SIZE);
      }

      // else: size is no greater than default max block
      // malloc a block of DEFAULT size
      free_node * new_block = (free_node *) malloc(DEFAULT_BLOCK + HEADER_SIZE);
      gl_total_size += (DEFAULT_BLOCK + HEADER_SIZE);
      new_block -> size = DEFAULT_BLOCK;
      new_block -> next = NULL;

      if (DEFAULT_BLOCK - (size) < MAX_GAP) {
       // gives the whole block
        addr = new_block;
      } else {
        addr = divide(addr, new_block, size);  // divide the block
        insert_block(new_block);  // insert the new_block into free_list
      }
    } else {  // current -> next is enough
      if (current -> next -> size - (size) < MAX_GAP) {
        // gives the whole block
        addr = current -> next;
        current -> next = current -> next -> next;
      } else {  // divide the block
        addr = divide(addr, current -> next, size);
      }
    }
  }
  return addr + 1;
}

// divides a block of given size out of the target block
// and gives the pointer of the new split block to addr
free_node * divide(free_node * addr, free_node * target, uintptr_t size) {
  target -> size -= (size + HEADER_SIZE);
  addr = (free_node *)((uintptr_t) target + target -> size + HEADER_SIZE);
  addr -> size = size;
  addr -> next = NULL;
  return addr;
}
